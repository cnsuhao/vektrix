/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009-2010 Fuse-Software (tm)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "vtxswfShapeParser.h"
#include "vtxswfParser.h"

#include "vtxFileHelper.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"
#include "vtxSubshapeResource.h"
#include "vtxswfStructParserHelper.h"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		void ShapeParser::handleDefineShape(const TagTypes& tag_type, MemoryBlockReader& tag_reader, SwfParser* parser)
		{
			// clear all lists
			// -> FLASH
			mFlashShape.clear();

			// -> VEKTRIX
			mFillstyles.clear();
			mLinestyles.clear();
			mChunkLists.clear();
			mSubShapeList.clear();
			mSubLineList.clear();

			UI16 shape_id = tag_reader.readUI16();

			RECT bounds;
			ParserHelper::readRect(tag_reader, bounds);
			if(tag_type == TT_DefineShape4)
			{
				RECT edge_bounds;
				ParserHelper::readRect(tag_reader, edge_bounds);
				tag_reader.readUI8(); // line flags
			}

			ShapeResource* shape_resource = new ShapeResource(StringHelper::toString(shape_id));
			parser->getCurrentFile()->addResource(shape_resource);

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			shape_resource->setBoundingBox(box);

			// parse the flash shape
			//tag_reader.readShapeWithStyle(tag_type, mFlashShape);

			// now the actual "translation" to a vektrix shape takes place

			// filters out unused fill-/linestyles, for some reason SWF can contain these
			getFlashStyles();

			// get the flash shape elements
			getFlashChunks();

			// process the flash data
			generateSubshapes();
			generateSublines();
		}
		//-----------------------------------------------------------------------
		void ShapeParser::getFlashStyles()
		{
			ShapeElementList::iterator it = mFlashShape.elements.begin();
			ShapeElementList::iterator end = mFlashShape.elements.end();

			while(it != end)
			{
				const SHAPEELEMENT& se = *it;

				// store FILLSTYLE 0
				if(mFillstyles.find(se.fill0) == mFillstyles.end() && se.fill0 > 0)
				{
					const FILLSTYLE& fillstyle = mFlashShape.fillstyles.at(se.fill0 - 1);
					mFillstyles.insert(std::make_pair(se.fill0, fillstyle));
				}

				// store FILLSTYLE 1
				if(mFillstyles.find(se.fill1) == mFillstyles.end() && se.fill1 > 0)
				{
					const FILLSTYLE& fillstyle = mFlashShape.fillstyles.at(se.fill1 - 1);
					mFillstyles.insert(std::make_pair(se.fill1, fillstyle));
				}

				// store LINESTYLE
				if(mLinestyles.find(se.line) == mLinestyles.end() && se.line > 0)
				{
					const LINESTYLE& linestyle = mFlashShape.linestyles.at(se.line - 1);
					mLinestyles.insert(std::make_pair(se.line, linestyle));
				}

				++it;
			}
		}
		//-----------------------------------------------------------------------
		void ShapeParser::getFlashChunks()
		{
			uint count = 0;

			FillstyleMap::iterator fill_it = mFillstyles.begin();
			FillstyleMap::iterator fill_end = mFillstyles.end();

			while(fill_it != fill_end)
			{
				ContourElementList curr_chunk;

				// get and store the flash elements
				const SHAPEELEMENT* prev_elem = NULL;

				ShapeElementList::iterator elem_it = mFlashShape.elements.begin();
				ShapeElementList::iterator elem_end = mFlashShape.elements.end();
				while(elem_it != elem_end)
				{
					const SHAPEELEMENT& se = *elem_it;

					if(prev_elem)
					{
						if((se.fill0 == fill_it->first || 
							se.fill1 == fill_it->first) && 
							se.type != SET_MOVE)
						{
							switch(se.type)
							{
							case SET_MOVE:
							case SET_LINE:
								{
									ContourElement elem;
									elem.type = CID_LINE;

									elem.p0.x = prev_elem->x;
									elem.p0.y = prev_elem->y;

									elem.p1.x = se.x;
									elem.p1.y = se.y;

									curr_chunk.push_back(elem);
									++count;
								}
								break;

							case SET_BEZIER:
								{
									ContourElement elem;
									elem.type = CID_BEZIER;

									elem.p0.x = prev_elem->x;
									elem.p0.y = prev_elem->y;

									elem.ctrl.x = se.cx;
									elem.ctrl.y = se.cy;

									elem.p1.x = se.x;
									elem.p1.y = se.y;

									curr_chunk.push_back(elem);
									++count;
								}
								break;
							}
						}
					}
					prev_elem = &se;
					++elem_it;
				}
				mChunkLists[fill_it->first] = curr_chunk;
				++fill_it;
			}
		}
		//-----------------------------------------------------------------------
		void ShapeParser::generateSubshapes()
		{
			// loop through all fillstyles
			FillstyleMap::iterator fill_it = mFillstyles.begin();
			FillstyleMap::iterator fill_end = mFillstyles.end();
			while(fill_it != fill_end)
			{
				ContourChunkMap::iterator main_it = mChunkLists.find(fill_it->first);
				if(main_it == mChunkLists.end())
				{
					VTX_WARN("Error: ChunkMap with fillstyle %d was not found.", fill_it->first);
					continue;
				}

				ContourElementList& chunks = main_it->second;

				SubShape subshape;
				subshape.fillstyle = fill_it->first;

				enum States
				{
					STATE_INIT = 0, 
					STATE_SEARCH
				} state = STATE_INIT;

				ContourElement first_element;

				ContourElementList::iterator elem_it = chunks.begin();
				ContourElementList::iterator elem_end = chunks.end();
				while(elem_it != elem_end)
				{
					switch(state)
					{
					case STATE_INIT:
						{
							subshape.elements.push_back(*elem_it);
							subshape.elements.back().isStartElement = true;
							first_element = subshape.elements.back();
							chunks.erase(elem_it);

							state = STATE_SEARCH;
							elem_it = chunks.begin();
							elem_end = chunks.end();
							continue;
						}
						break;

					case STATE_SEARCH:
						{
							if(subshape.elements.back().connectsTo(*elem_it))
							{
								// found a element that connects
								//std::cout << "found a element that connects" << std::endl;
								subshape.elements.push_back(*elem_it);
								chunks.erase(elem_it);

								state = STATE_SEARCH;
								elem_it = chunks.begin();
								elem_end = chunks.end();
								continue;
							}
							else if((*elem_it).connectsReverseTo(subshape.elements.back()))
							{
								// found a element that connects reverse
								subshape.elements.push_back(*elem_it);
								subshape.elements.back().reverse();
								chunks.erase(elem_it);

								state = STATE_SEARCH;
								elem_it = chunks.begin();
								elem_end = chunks.end();
								continue;
							}
						}
						break;
					}

					if(subshape.elements.back().connectsTo(first_element) && subshape.elements.size() > 1)
					{
						// reached a closed loop
						state = STATE_INIT;
						elem_it = chunks.begin();
						elem_end = chunks.end();
						continue;
					}

					++elem_it;

				} // while(elements)
				VTX_DEBUG_ASSERT(!chunks.size(), "There should be no elements left here");

				// store the result
				mSubShapeList.push_back(subshape);

				++fill_it;
			} // while (fillstyles)
		}
		//-----------------------------------------------------------------------
		void ShapeParser::generateSublines()
		{}
		//-----------------------------------------------------------------------
	}
}
