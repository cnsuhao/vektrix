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

namespace vtx { namespace swf {
	//-----------------------------------------------------------------------
	void ShapeParser::handleDefineShape(const TagTypes& tag_type, SwfParser* parser)
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

		UI16 shape_id = parser->readU16();

		RECT bounds = parser->readRect();

		if(tag_type == TT_DefineShape4)
		{
			parser->readRect(); // edge bounds
			parser->readU8(); // line flags
		}

		ShapeResource* shape_resource = new ShapeResource(StringHelper::toString(shape_id));
		parser->getCurrentFile()->addResource(shape_resource);

		BoundingBox box(
			Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
			Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

		shape_resource->setBoundingBox(box);

		// parse the flash shape
		parser->readShapeWithStyle(tag_type, mFlashShape);

		// now the actual "translation" to a vektrix shape takes place

		// filters out unused fill-/linestyles, for some reason SWF can contain these
		getFlashStyles();

		// get the flash shape elements
		getFlashChunks();

		// process the flash data
		generateSubshapes();
		generateSublines();

		// write the processed data to our own format
		writeFillstyles(shape_id, parser->getCurrentFile());
		writeSubshapes(shape_resource);
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
			} // while(shape_elements)

			mChunkLists[fill_it->first] = curr_chunk;

			++fill_it;
		} // while(fillstyle)

		//std::cout << "Num Elements: " << count << std::endl;

#if defined DEBUG_FLASH_SHAPES && defined _DEBUG

		if(!FileHelper::doesDirectoryExist(DEBUG_OUTPUT_PATH))
			return;

		// DEBUG
		char filename[512];
		sprintf_s(filename, "%sall_elements.txt", DEBUG_OUTPUT_PATH);
		FILE* file = fopen(filename, "w");

		ShapeElementList::iterator elem_it = mFlashShape.elements.begin();
		ShapeElementList::iterator elem_end = mFlashShape.elements.end();
		while(elem_it != elem_end)
		{
			SHAPEELEMENT& se = *elem_it;

			if(se.type == SET_BEZIER)
			{
				fprintf(file, "%4.2f %4.2f (C) [%d|%d][%d]\n", 
					se.cx / 20.0f, -se.cy / 20.0f, 
					se.fill0, se.fill1, 
					se.line);
				fprintf(file, "%4.2f %4.2f (S) [%d|%d][%d]\n", 
					se.x / 20.0f, -se.y / 20.0f, 
					se.fill0, se.fill1, 
					se.line);
			}
			else if(se.type == SET_LINE)
			{
				fprintf(file, "%4.2f %4.2f (L) [%d|%d][%d]\n", 
					se.x / 20.0f, -se.y / 20.0f, 
					se.fill0, se.fill1, 
					se.line);
			}
			else if(se.type == SET_MOVE)
			{
				fprintf(file, "%4.2f %4.2f (M) [%d|%d][%d]\n", 
					se.x / 20.0f, -se.y / 20.0f, 
					se.fill0, se.fill1, 
					se.line);
			}

			++elem_it;
		} // while(shape_elements)

		fclose(file);

		// DEBUG chunks
		ContourChunkMap::iterator map_it = mChunkLists.begin();
		ContourChunkMap::iterator map_end = mChunkLists.end();
		for( ; map_it != map_end; ++map_it)
		{
			char filename[512];
			sprintf_s(filename, "%schunks_%d.txt", DEBUG_OUTPUT_PATH, map_it->first);
			FILE* file = fopen(filename, "w");

			ContourElementList::const_iterator chunk_it = map_it->second.begin();
			ContourElementList::const_iterator chunk_end = map_it->second.end();
			for( ; chunk_it != chunk_end; ++chunk_it)
			{
				debug_contour_element(*chunk_it, file);
			}

			fclose(file);
		}
#endif
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
							//std::cout << "found a element that connects reverse" << std::endl;
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
					//std::cout << "reached a closed loop" << std::endl;
					state = STATE_INIT;
					elem_it = chunks.begin();
					elem_end = chunks.end();
					continue;
				}

				++elem_it;

			} // while(elements)

			//std::cout << "ELEMENTS LEFT: " << chunks.size() << std::endl;
			VTX_DEBUG_ASSERT(!chunks.size(), "There should be no elements left here");

#if defined DEBUG_FLASH_SHAPES && defined _DEBUG

			if(FileHelper::doesDirectoryExist(DEBUG_OUTPUT_PATH))
			{
				char filename[512];
				sprintf_s(filename, "%ssubshapes_%d.txt", DEBUG_OUTPUT_PATH, fill_it->first);
				FILE* file = fopen(filename, "w");

				elem_it = subshape.elements.begin();
				elem_end = subshape.elements.end();
				while(elem_it != elem_end)
				{
					if((*elem_it).isStartElement)
					{
						fprintf(file, "start\n");
					}
					debug_contour_element(*elem_it, file);
					++elem_it;
				}

				fclose(file);
			}
#endif

			// store the result
			mSubShapeList.push_back(subshape);

			++fill_it;
		} // while (fillstyles)
	}
	//-----------------------------------------------------------------------
	void ShapeParser::generateSublines()
	{

	}
	//-----------------------------------------------------------------------
	void ShapeParser::writeFillstyles(const UI16& shape_id, File* file)
	{
		FillstyleMap::iterator it = mFillstyles.begin();
		FillstyleMap::iterator end = mFillstyles.end();
		while(it != end)
		{
			MaterialResource* material = NULL;

			switch(it->second.type)
			{
				// COLOR
			case FST_Solid:
				{
					const COLOR& swfColor = it->second.color;
					material = new MaterialResource(
						StringHelper::toString(shape_id)+"->"+StringHelper::toString(it->first), 
						MaterialResource::MT_COLOR);

					Color color = Color(
						(float)swfColor.red/255.0f, 
						(float)swfColor.green/255.0f, 
						(float)swfColor.blue/255.0f, 
						(float)swfColor.alpha/255.0f);

					material->setColor(color);
				}
				break;

			case FST_RepeatingBitmap:
			case FST_ClippedBitmap:
			case FST_NonSmoothedRepeatingBitmap:
			case FST_NonSmoothedClippedBitmap:
				{
					material = new MaterialResource(
						StringHelper::toString(shape_id)+"->"+StringHelper::toString(it->first), 
						MaterialResource::MT_IMAGE);
					material->setImageID(StringHelper::toString(it->second.bitmapId));
				}
				break;

			case FST_LinearGradient:
			case FST_RadialGradient:
				{
					material = new MaterialResource(
						StringHelper::toString(shape_id)+"->"+StringHelper::toString(it->first), 
						(it->second.type == FST_LinearGradient)?
						MaterialResource::MT_LINEAR_GRADIENT:
					MaterialResource::MT_RADIAL_GRADIENT);

					const MATRIX& m = it->second.matrix;
					Matrix matrix = Matrix(
						m.sx/65536.0f, m.cx/65536.0f, m.tx/20.0f, 
						m.cy/65536.0f, m.sy/65536.0f, m.ty/20.0f);

					material->setTransformMatrix(matrix);

					const FILLSTYLE::GradientMap& gradient = it->second.gradient;
					FILLSTYLE::GradientMap::const_iterator grd_it = gradient.begin();
					FILLSTYLE::GradientMap::const_iterator grd_end = gradient.end();

					while(grd_it != grd_end)
					{
						const COLOR& swfColor = grd_it->second;

						Color color = Color(
							(float)swfColor.red/255.0f, 
							(float)swfColor.green/255.0f, 
							(float)swfColor.blue/255.0f, 
							(float)swfColor.alpha/255.0f);

						material->setGradientColor(grd_it->first, color);
						++grd_it;
					}
				}
				break;

			default:
				{
					VTX_EXCEPT("vtxswf: Unimplemented Material Type");
				}
				break;
			};

			file->addResource(material);

			++it;
		}// while(fillstyles)
	}
	//-----------------------------------------------------------------------
	void ShapeParser::writeSubshapes(ShapeResource* shape_resource)
	{
		File* file = shape_resource->getFile();

		SubShapeList::iterator subshape_it = mSubShapeList.begin();
		SubShapeList::iterator subshape_end = mSubShapeList.end();
		while(subshape_it != subshape_end)
		{
			String material_id = 
				shape_resource->getID() + 
				"->" + 
				StringHelper::toString((*subshape_it).fillstyle);

			MaterialResource* mat = static_cast<MaterialResource*>(file->getResource(material_id, "Material"));

			if(!mat)
			{
				VTX_EXCEPT("The requested Resource with the ID: %d is no MaterialResource.", (*subshape_it).fillstyle);
			}

			SubshapeResource* subshape = new SubshapeResource();
			subshape->setMaterial(mat);
			shape_resource->addSubshapeResource(subshape);

			ContourElementList::iterator element_it = (*subshape_it).elements.begin();
			ContourElementList::iterator element_end = (*subshape_it).elements.end();
			while(element_it != element_end)
			{
				// the current element
				ContourElement& element = *element_it;

				// what type is it?
				switch(element.type)
				{
				case CID_LINE:
					{
						if(element.isStartElement)
						{
							ShapeElement shape_element;
							shape_element.type = ShapeElement::SID_MOVE_TO;
							shape_element.pos = Vector2(element.p0.x/20.0f, element.p0.y/20.0f);
							subshape->addShapeElement(shape_element);
						}

						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_LINE_TO;
						shape_element.pos = Vector2(element.p1.x/20.0f, element.p1.y/20.0f);

						subshape->addShapeElement(shape_element);
					}
					break;
				case CID_BEZIER:
					{
						if(element.isStartElement)
						{
							ShapeElement shape_element;
							shape_element.type = ShapeElement::SID_MOVE_TO;
							shape_element.pos = Vector2(element.p0.x/20.0f, element.p0.y/20.0f);
							subshape->addShapeElement(shape_element);
						}

						ShapeElement shape_element;
						shape_element.type = ShapeElement::SID_CURVE_TO;
						shape_element.ctrl = Vector2(element.ctrl.x/20.0f, element.ctrl.y/20.0f);
						shape_element.pos = Vector2(element.p1.x/20.0f, element.p1.y/20.0f);

						subshape->addShapeElement(shape_element);
					}
					break;
				}; // switch(element.type)

				++element_it;

			} // for(elements)

			++subshape_it;

		} // for(subshapes)
	}
	//-----------------------------------------------------------------------
	void SwfParser::debug_contour_element(const ContourElement& element, FILE* file)
	{
#if defined DEBUG_FLASH_SHAPES && defined _DEBUG

		if(!FileHelper::doesDirectoryExist(DEBUG_OUTPUT_PATH))
			return;

		switch(element.type)
		{
			//case CID_MOVE:
			//	if(file)
			//		fprintf(file, "%4.2f %4.2f (M)\n", element.x / 20.0f, element.y / 20.0f);
			//else
			//	printf("%4.2f %4.2f (M)\n", element.x / 20.0f, element.y / 20.0f);
			break;

		case CID_LINE:
			if(file)
			{
				fprintf(file, "%4.2f %4.2f (L0)\n", element.p0.x / 20.0f, element.p0.y / 20.0f);
				fprintf(file, "%4.2f %4.2f (L1)\n\n", element.p1.x / 20.0f, element.p1.y / 20.0f);
			}
			//else
			//	printf("%4.2f %4.2f (L)\n", element.x / 20.0f, element.y / 20.0f);
			break;

		case CID_BEZIER:
			if(file)
			{
				fprintf(file, "%4.2f %4.2f (B0)\n", element.p0.x / 20.0f, element.p0.y / 20.0f);
				fprintf(file, "%4.2f %4.2f (C)\n", element.ctrl.x / 20.0f, element.ctrl.y / 20.0f);
				fprintf(file, "%4.2f %4.2f (B1)\n\n", element.p1.x / 20.0f, element.p1.y / 20.0f);
			}
			//	fprintf(file, "%4.2f %4.2f (S)\n", element.x / 20.0f, element.y / 20.0f);
			//else
			//	printf("%4.2f %4.2f (S)\n", element.x / 20.0f, element.y / 20.0f);
			break;
		}
#endif
	}
	//-----------------------------------------------------------------------
	void SwfParser::debug_shape_element(const ShapeElement& element, FILE* file)
	{
#if defined DEBUG_FLASH_SHAPES && defined _DEBUG

		if(!FileHelper::doesDirectoryExist(DEBUG_OUTPUT_PATH))
			return;

		switch(element.type)
		{
		case ShapeElement::SID_MOVE_TO:
			fprintf(file, "%4.2f %4.2f (M)\n", element.pos.x, element.pos.y);
			break;

		case ShapeElement::SID_LINE_TO:
			fprintf(file, "%4.2f %4.2f (L)\n", element.pos.x, element.pos.y);
			break;

		case ShapeElement::SID_CURVE_TO:
			fprintf(file, "%4.2f %4.2f (C)\n", element.ctrl.x, element.ctrl.y);
			fprintf(file, "%4.2f %4.2f (S)\n", element.pos.x, element.pos.y);
			break;
		}
#endif
	}
	//-----------------------------------------------------------------------
}}
