/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/

Copyright (c) 2009 Fuse-Software (tm)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.txt.
-----------------------------------------------------------------------------
*/
#include "vtxswfShapeHandler.h"

#include "vtxFile.h"
#include "vtxLogManager.h"
#include "vtxMaterialResource.h"
#include "vtxShapeResource.h"
#include "vtxStringHelper.h"
#include "vtxSubshapeResource.h"

//#define DEBUG_FLASH_SHAPES
//#define DEBUG_OUTPUT_PATH "C:/vektrix_debug/"

namespace vtx
{
	namespace swf
	{
		//-----------------------------------------------------------------------
		ShapeHandler::ShapeHandler() 
			: mFlashID(0), 
			mCurrentFile(NULL), 
			mShapeResource(NULL)
		{

		}
		//-----------------------------------------------------------------------
		ShapeHandler::~ShapeHandler()
		{

		}
		//-----------------------------------------------------------------------
		void ShapeHandler::handleShape(TAG* swfTag, File* file)
		{
			mCurrentFile = file;

			// clear all lists
			mChunks.clear();
			mFillstyleList.clear();
			mLinestyleList.clear();
			mSubShapeList.clear();
			mSubLineList.clear();

			// flash ID of the current shape
			mFlashID = swf_GetU16(swfTag);

			swfTag->pos = 0;
			swfTag->readBit = 0;

			// parse the swf shape from the given tag
			SHAPE2 shape;
			swf_ParseDefineShape(swfTag, &shape);

			// the vtx shape
			mShapeResource = new ShapeResource(StringHelper::toString(mFlashID), "");
			file->addResource(mShapeResource);

			BoundingBox box(
				Vector2(shape.bbox->xmax/20.0f, shape.bbox->ymax/20.0f), 
				Vector2(shape.bbox->xmin/20.0f, shape.bbox->ymin/20.0f));

			mShapeResource->setBoundingBox(box);

			VTX_LOG("SWF DEBUG: added Shape with id %d", mFlashID);

			// process the flash fill- and linestyles
			get_flash_styles(shape);

			// get the flash elements from swftools
			get_flash_chunks(shape);

			// generate the subshapes
			generate_subshapes();

			// generate the sublines
			generate_sublines();

			printf("----------------\n");
			printf("writing SHAPE...\nID: %d\nfillstyles: %d (%d unused)\nlinestyles: %d (%d unused)\nshape-definitions: %d\nline-definitions: %d\n", 
				mFlashID, 
				shape.numfillstyles, 
				shape.numfillstyles - mFillstyleList.size(), 
				shape.numlinestyles, 
				shape.numlinestyles - mLinestyleList.size(), 
				mSubShapeList.size(), 
				mSubLineList.size());
			printf("----------------\n");

			//--------------------
			// write FILLSTYLES
			//--------------------

			// write all fillstyles
			// they were pre-processed and are waiting in the FillstyleList
			write_fillstyles();


			//--------------------
			// write LINESTYLES
			//--------------------

			// write all linestyles
			// they were pre-processed and are waiting in the LinestyleList
			//for(LinestyleList::iterator it = mLinestyleList.begin(); 
			//	it != mLinestyleList.end(); 
			//	it++)
			//{
			//	write_linestyle(it->second, it->first, file);
			//}

			//---------------------------
			// write the SUBSHAPE-DATA
			//---------------------------

			// write all subshapes
			// they were pre-processed and are waiting in the SubShapeList
			write_subshapes();

			//--------------------------
			// write the SUBLINE-DATA
			//--------------------------

			// write all sublines
			// they were pre-processed and are waiting in the SubLineList
			//for(SubLineList::iterator it = mSubLineList.begin(); 
			//	it != mSubLineList.end(); 
			//	it++)
			//{
			//	write_subline(*it, file);
			//}

			mFlashID = 0;
			mCurrentFile = NULL;
			mShapeResource = NULL;
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::get_flash_styles(const SHAPE2& shape)
		{
			SHAPELINE* line = shape.lines;

			// store used and discard unused styles (fill_0, fill_1, line)
			while(line)
			{
				unsigned int curr_fillstyle_0 = line->fillstyle0;
				unsigned int curr_fillstyle_1 = line->fillstyle1;
				unsigned int curr_linestyle = line->linestyle;

				// store FILLSTYLE 0
				if(mFillstyleList.find(curr_fillstyle_0) == mFillstyleList.end() && curr_fillstyle_0 > 0)
				{
					FILLSTYLE* fillstyle = &shape.fillstyles[curr_fillstyle_0 - 1];

					if(fillstyle->type == 0x00 ||
						fillstyle->type == 0x10 || 
						fillstyle->type == 0x12 || 
						fillstyle->type == 0x40 || 
						fillstyle->type == 0x41)
					{
						mFillstyleList.insert(FillstyleList::value_type(curr_fillstyle_0, fillstyle));
					}
				}

				// store FILLSTYLE 1
				if(mFillstyleList.find(curr_fillstyle_1) == mFillstyleList.end() && curr_fillstyle_1 > 0)
				{
					FILLSTYLE* fillstyle = &shape.fillstyles[curr_fillstyle_1 - 1];

					if(fillstyle->type == 0x00 ||
						fillstyle->type == 0x10 || 
						fillstyle->type == 0x12 || 
						fillstyle->type == 0x40 || 
						fillstyle->type == 0x41)
					{
						mFillstyleList.insert(FillstyleList::value_type(curr_fillstyle_1, fillstyle));
					}
				}

				// store LINESTYLE
				if(mLinestyleList.find(curr_linestyle) == mLinestyleList.end() && curr_linestyle > 0)
				{
					LINESTYLE* linestyle = &shape.linestyles[curr_linestyle - 1];

					mLinestyleList.insert(LinestyleList::value_type(curr_linestyle, linestyle));
				}

				line = line->next;
			} // while(line)

#ifdef DEBUG_FLASH_SHAPES
			// DEBUG
			char filename[512];
			sprintf_s(filename, "%sfillstyles.txt", DEBUG_OUTPUT_PATH);
			FILE* file = fopen(filename, "w");

			fprintf(file, "FILL-STYLES\n");

			FillstyleList::iterator it = mFillstyleList.begin();
			FillstyleList::iterator end = mFillstyleList.end();
			for( ; it != end; ++it)
			{
				fprintf(file, "%d -> %4.2f %4.2f %4.2f %4.2f\n", 
					it->first, 
					it->second->color.r/255.0f, 
					it->second->color.g/255.0f, 
					it->second->color.b/255.0f, 
					it->second->color.a/255.0f);
			}

			fprintf(file, "\nLINE-STYLES\n");

			//LinestyleList::iterator it2 = mLinestyleList.begin();
			//LinestyleList::iterator end2 = mLinestyleList.end();
			//for( ; it2 != end2; ++it2)
			//{
			//	fprintf(file, "%d -> %4.2f %4.2f %4.2f %4.2f\n", 
			//		it->first, 
			//		it->second->color.r/255.0f, 
			//		it->second->color.g/255.0f, 
			//		it->second->color.b/255.0f, 
			//		it->second->color.a/255.0f);
			//}

			fclose(file);
#endif
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::get_flash_chunks(const SHAPE2& shape)
		{
			size_t count = 0;

			FillstyleList::iterator fill_it = mFillstyleList.begin();
			FillstyleList::iterator fill_end = mFillstyleList.end();
			for( ; fill_it != fill_end; ++fill_it)
			{
				SHAPELINE* prev_line = NULL;
				SHAPELINE* line = shape.lines;

				ContourElementList curr_chunk;

				// get and store the flash elements
				while(line)
				{
					if(prev_line)
					{
						if((line->fillstyle0 == fill_it->first || 
							line->fillstyle1 == fill_it->first) && 
							line->type != moveTo)
						{
							switch(line->type)
							{
							case moveTo:
							case lineTo:
								{
									ContourElement elem;
									elem.type = CID_LINE;

									elem.p0.x = prev_line->x;
									elem.p0.y = -prev_line->y;

									elem.p1.x = line->x;
									elem.p1.y = -line->y;

									curr_chunk.push_back(elem);
									++count;
								}
								break;

							case splineTo:
								{
									ContourElement elem;
									elem.type = CID_BEZIER;

									elem.p0.x = prev_line->x;
									elem.p0.y = -prev_line->y;

									elem.ctrl.x = line->sx;
									elem.ctrl.y = -line->sy;

									elem.p1.x = line->x;
									elem.p1.y = -line->y;

									curr_chunk.push_back(elem);
									++count;
								}
								break;
							}
						}
					}

					prev_line = line;
					line = line->next;
				} // while(line)

				mChunks[fill_it->first] = curr_chunk;

			} // for(fillstyle)

			std::cout << "Num Elements: " << count << std::endl;

#ifdef DEBUG_FLASH_SHAPES
			// DEBUG
			char filename[512];
			sprintf_s(filename, "%sall_elements.txt", DEBUG_OUTPUT_PATH);
			FILE* file = fopen(filename, "w");

			SHAPELINE* line = shape.lines;

			while(line)
			{
				if(line->type == splineTo)
				{
					fprintf(file, "%4.2f %4.2f (C) [%d|%d][%d]\n", 
						line->sx / 20.0f, -line->sy / 20.0f, 
						line->fillstyle0, line->fillstyle1, 
						line->linestyle);
					fprintf(file, "%4.2f %4.2f (S) [%d|%d][%d]\n", 
						line->x / 20.0f, -line->y / 20.0f, 
						line->fillstyle0, line->fillstyle1, 
						line->linestyle);
				}
				else if(line->type == lineTo)
				{
					fprintf(file, "%4.2f %4.2f (L) [%d|%d][%d]\n", 
						line->x / 20.0f, -line->y / 20.0f, 
						line->fillstyle0, line->fillstyle1, 
						line->linestyle);
				}
				else if(line->type == moveTo)
				{
					fprintf(file, "%4.2f %4.2f (M) [%d|%d][%d]\n", 
						line->x / 20.0f, -line->y / 20.0f, 
						line->fillstyle0, line->fillstyle1, 
						line->linestyle);
				}

				line = line->next;

			} // while(line)

			fclose(file);

			// DEBUG chunks
			ContourChunkMap::iterator map_it = mChunks.begin();
			ContourChunkMap::iterator map_end = mChunks.end();
			for( ; map_it != map_end; ++map_it)
			{
				char filename[512];
				sprintf_s(filename, "%schunks_%d.txt", DEBUG_OUTPUT_PATH, map_it->first);
				FILE* file = fopen(filename, "w");

				ContourElementList::const_iterator chunk_it = map_it->second.begin();
				ContourElementList::const_iterator chunk_end = map_it->second.end();
				for( ; chunk_it != chunk_end; ++chunk_it)
				{
					debug_element(*chunk_it, file);
				}

				fclose(file);
			}
#endif
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::debug_element(const ContourElement& element, FILE* file)
		{
#ifdef DEBUG_FLASH_SHAPES
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
		void ShapeHandler::debug_shape_element(const SubshapeResource::ShapeElement& element, FILE* file)
		{
#ifdef DEBUG_FLASH_SHAPES
			switch(element.type)
			{
			case SubshapeResource::ShapeElement::SID_MOVE_TO:
				fprintf(file, "%4.2f %4.2f (M)\n", element.pos.x, element.pos.y);
				break;

			case SubshapeResource::ShapeElement::SID_LINE_TO:
				fprintf(file, "%4.2f %4.2f (L)\n", element.pos.x, element.pos.y);
				break;

			case SubshapeResource::ShapeElement::SID_CURVE_TO:
				fprintf(file, "%4.2f %4.2f (C)\n", element.ctrl.x, element.ctrl.y);
				fprintf(file, "%4.2f %4.2f (S)\n", element.pos.x, element.pos.y);
				break;
			}
#endif
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::generate_subshapes()
		{
			// loop through all fillstyles
			FillstyleList::iterator fill_it = mFillstyleList.begin();
			FillstyleList::iterator fill_end = mFillstyleList.end();
			for( ; fill_it != fill_end; ++fill_it)
			{
				//if(fill_it->first != 12)
				//{
				//	continue;
				//}

				ContourChunkMap::iterator main_it = mChunks.find(fill_it->first);
				if(main_it == mChunks.end())
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
				assert("There should be no elements left here" && !chunks.size());

#ifdef DEBUG_FLASH_SHAPES
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
					debug_element(*elem_it, file);
					++elem_it;
				}

				fclose(file);

#endif

				// store the result
				mSubShapeList.push_back(subshape);
			} // for END (fillstyles)
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::generate_sublines()
		{

		}
		//-----------------------------------------------------------------------
		void ShapeHandler::write_fillstyles()
		{
			for(FillstyleList::iterator it = mFillstyleList.begin(); 
				it!=mFillstyleList.end(); 
				it++)
			{
				MaterialResource* material = NULL;// new MaterialResource(StringHelper::toString(it->first), )
					//write_fillstyle(it->second, it->first, file);

				switch(it->second->type)
				{
				// COLOR
				case 0x00:
					{
						const RGBA& swfColor = it->second->color;
						material = new MaterialResource(StringHelper::toString(mFlashID)+"->"+StringHelper::toString(it->first), MaterialResource::MT_COLOR);

						Color color = Color(
							(float)swfColor.r/255.0f, 
							(float)swfColor.g/255.0f, 
							(float)swfColor.b/255.0f, 
							(float)swfColor.a/255.0f);

						material->setColor(color);

						//VTX_LOG("SWF COLOR: %d", it->first);
						//VTX_LOG("SWF COLOR: %s", StringHelper::toString(color).c_str());
					}
					break;

				// GRADIENT
				case 0x10: case 0x11: case 0x12: case 0x13:
					{

					}
					break;

				// BITMAP1 ??
				case 0x40: case 0x42:
					{

					}
					break;

				// BITMAP2 ??
				case 0x41: case 0x43:
					{

					}
					break;

				default:
					{
						VTX_EXCEPT("vtxswf: Unknown Material Type");
					}
					break;
				};

				//VTX_LOG("SWF DEBUG: added material with id %d", it->first);
				mCurrentFile->addResource(material);
			}// for(fillstyles)
		}
		//-----------------------------------------------------------------------
		void ShapeHandler::write_subshapes()
		{
			SubShapeList::iterator subshape_it = mSubShapeList.begin();
			for( ; subshape_it != mSubShapeList.end(); ++subshape_it)
			{
				MaterialResource* mat = dynamic_cast<MaterialResource*>(mCurrentFile->getResource(StringHelper::toString(mFlashID)+"->"+StringHelper::toString((*subshape_it).fillstyle)));

				if(!mat)
				{
					VTX_EXCEPT("The requested Resource with the ID: %d is no MaterialResource.", (*subshape_it).fillstyle);
				}

				SubshapeResource* subshape = new SubshapeResource();
				subshape->setMaterial(mat);
				mShapeResource->addSubshapeResource(subshape);

				ContourElementList::iterator element_it = (*subshape_it).elements.begin();
				for( ; element_it != (*subshape_it).elements.end(); ++element_it)
				{
					// the current element
					ContourElement& element = *element_it;

					// what type is it?
					switch(element.type)
					{
					//case CID_MOVE:
					//	{
					//		SubshapeResource::ShapeElement shape_element;

					//		shape_element.type = SubshapeResource::ShapeElement::SID_MOVE_TO;
					//		//shape_element.pos = Vector2(element.x/20.0f, element.y/20.0f);

					//		subshape->addShapeElement(shape_element);

					//		//debug_shape_element(shape_element, file);
					//	}
					//	break;
					case CID_LINE:
						{
							if(element.isStartElement)
							{
								SubshapeResource::ShapeElement shape_element;
								shape_element.type = SubshapeResource::ShapeElement::SID_MOVE_TO;
								shape_element.pos = Vector2(element.p0.x/20.0f, element.p0.y/20.0f);
								subshape->addShapeElement(shape_element);
							}

							SubshapeResource::ShapeElement shape_element;
							shape_element.type = SubshapeResource::ShapeElement::SID_LINE_TO;
							shape_element.pos = Vector2(element.p1.x/20.0f, element.p1.y/20.0f);
							subshape->addShapeElement(shape_element);

							//debug_shape_element(shape_element, file);
						}
						break;
					case CID_BEZIER:
						{
							if(element.isStartElement)
							{
								SubshapeResource::ShapeElement shape_element;
								shape_element.type = SubshapeResource::ShapeElement::SID_MOVE_TO;
								shape_element.pos = Vector2(element.p0.x/20.0f, element.p0.y/20.0f);
								subshape->addShapeElement(shape_element);
							}

							SubshapeResource::ShapeElement shape_element;
							shape_element.type = SubshapeResource::ShapeElement::SID_CURVE_TO;
							shape_element.ctrl = Vector2(element.ctrl.x/20.0f, element.ctrl.y/20.0f);
							shape_element.pos = Vector2(element.p1.x/20.0f, element.p1.y/20.0f);

							subshape->addShapeElement(shape_element);
						}
						break;
					//case CID_CONTROL_POINT:
					//	{
					//		debug_element(element, file);

					//		SubshapeResource::ShapeElement shape_element;

					//		shape_element.type = SubshapeResource::ShapeElement::SID_CURVE_TO;

					//		shape_element.ctrl = Vector2(element.x/20.0f, element.y/20.0f);

					//		// next element
					//		++element_it;

					//		if(element_it == (*subshape_it).elements.end())
					//		{
					//			assert("Unexpected end of element list" && false);
					//		}

					//		element = *element_it;

					//		// element has to be a bezier
					//		element.type = CID_BEZIER;

					//		debug_element(element, file);

					//		//if(element.type != CID_BEZIER)
					//		//{
					//		//	assert("Unexpected element type, expected type BEZIER");
					//		//}

					//		shape_element.pos = Vector2(element.x/20.0f, element.y/20.0f);

					//		subshape->addShapeElement(shape_element);

					//		//debug_shape_element(shape_element, file);
					//	}
					//	break;
					}; // switch(element.type)
				} // for(elements)
			} // for(subshapes)

			std::cout << "finished conversion" << std::endl;
		}
		//-----------------------------------------------------------------------
	}
}
