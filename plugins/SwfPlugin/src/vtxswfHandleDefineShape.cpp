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
#include "vtxswfParser.h"

#include "vtxFileHelper.h"
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
		void SwfParser::handleDefineShape(const TagTypes& type)
		{
			// clear all lists
			// -> FLASH
			mFillstyleArray.clear();
			mLinestyleArray.clear();
			mShapeElements.clear();

			// -> VEKTRIX
			mFillstyles.clear();
			mLinestyles.clear();
			mChunkLists.clear();
			mSubShapeList.clear();
			mSubLineList.clear();

			UI16 shape_id = readU16();

			// reset bit buffer
			resetReadBits();
			RECT bounds = readRect();

			if(type == TT_DefineShape4)
			{
				resetReadBits();
				readRect(); // edge bounds
				readU8(); // line flags
			}

			ShapeResource* shape_resource = new ShapeResource(StringHelper::toString(shape_id));
			mCurrentFile->addResource(shape_resource);

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			shape_resource->setBoundingBox(box);

			parseFillstyleArray(type);
			parseLinestyleArray(type);

			resetReadBits();
			UI8 num_fill_bits = readUBits(4);
			UI8 num_line_bits = readUBits(4);

			//uint data_len = length - (mReadPos-start_pos);

			int x = 0;
			int y = 0;
			int fillstyle0 = 0;
			int fillstyle1 = 0;
			int linestyle = 0;

			while(true)
			{
				UI8 flags = readUBits(1);
				// edge record
				if(flags)
				{
					flags = readUBits(1);
					// straight edge
					if(flags)
					{
						UI8 num_bits = readUBits(4) + 2;

						// general line
						flags = readUBits(1);
						if(flags)
						{
							// line flag
							x += readSBits(num_bits); // delta x
							y += readSBits(num_bits); // delta y
						}
						// vertical/horizontal line
						else
						{
							UI8 vertical = readUBits(1);
							if(vertical)
							{
								y += readSBits(num_bits);;
							}
							else
							{
								x += readSBits(num_bits);;
							}
						}

						SHAPEELEMENT se;
						se.type = SET_LINE;
						se.x = x;
						se.y = y;
						se.cx = se.cy = 0;
						se.fill0 = fillstyle0;
						se.fill1 = fillstyle1;
						se.line = linestyle;

						//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
						mShapeElements.push_back(se);
					}
					// curved edge
					else
					{
						UI8 num_bits = readUBits(4) + 2;

						x += readSBits(num_bits); // delta x
						y += readSBits(num_bits); // delta y

						int cx = x;
						int cy = y;

						x += readSBits(num_bits); // delta x
						y += readSBits(num_bits); // delta y

						SHAPEELEMENT se;
						se.type = SET_BEZIER;
						se.x = x;
						se.y = y;
						se.cx = cx;
						se.cy = cy;
						se.fill0 = fillstyle0;
						se.fill1 = fillstyle1;
						se.line = linestyle;

						//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
						mShapeElements.push_back(se);
					}
				}
				// non-edge record
				else
				{
					flags = readUBits(5);

					// end-shape record
					if(!flags)
					{
						break;
					}
					// move
					if(flags & 1)
					{
						UI8 num_move_bits = readUBits(5);
						x = readSBits(num_move_bits);
						y = readSBits(num_move_bits);

						SHAPEELEMENT se;
						se.type = SET_MOVE;
						se.x = x;
						se.y = y;
						se.cx = se.cy = 0;
						se.fill0 = fillstyle0;
						se.fill1 = fillstyle1;
						se.line = linestyle;

						//std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x/20.0 << ", Y: " << y/20.0 << std::endl;
						mShapeElements.push_back(se);
					}
					// fillstyle 0
					if(flags & 2)
					{
						fillstyle0 = readUBits(num_fill_bits);
					}
					// fillstyle 1
					if(flags & 4)
					{
						fillstyle1 = readUBits(num_fill_bits);
					}
					// linestyle
					if(flags & 8)
					{
						linestyle = readUBits(num_line_bits);
					}
					// new styles
					if(flags & 16 && 
						(type == TT_DefineShape2 || 
						type == TT_DefineShape3))
					{
						//assert(false && "new styles not tested yet");
						parseFillstyleArray(type);
						parseLinestyleArray(type);
						num_fill_bits = readUBits(4);
						num_line_bits = readUBits(4);
					}
				}
			} // while(true)

			// now the actual "translation" to vektrix shape takes place

			// filters out unused fill-/linestyles, for some reason SWF can contain these
			getFlashStyles();

			// get the flash shape elements
			getFlashChunks();

			// process the flash data
			generateSubshapes();
			generateSublines();

			// write the processed data to our own format
			writeFillstyles(shape_id);
			writeSubshapes(shape_id, shape_resource);

			std::cout << "finished conversion" << std::endl;
		}
		//-----------------------------------------------------------------------
		void SwfParser::parseFillstyleArray(const TagTypes& type)
		{
			UI16 fillstyle_count = readU8();

			if(fillstyle_count == 255 && 
				(type == TT_DefineShape2 || 
				type == TT_DefineShape3))
			{
				fillstyle_count = readU16();
			}

			// FILLSTYLE ARRAY
			for(UI16 i=0; i<fillstyle_count; ++i)
			{
				UI8 fill_type = readU8();

				switch(fill_type)
				{
				case FST_Solid:
					{
						FILLSTYLE fs;
						fs.type = FST_Solid;
						fs.color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
						mFillstyleArray.push_back(fs);
					}
					break;

				case FST_LinearGradient:
				case FST_RadialGradient:
					{
						FILLSTYLE fs;
						fs.type = (FillStyleType)fill_type;
						fs.matrix = readMatrix();
						resetReadBits();

						UI8 spread_mode = readUBits(2);
						UI8 interp_mode = readUBits(2);
						UI8 num_gradients = readUBits(4);

						for(UI8 j=0; j<num_gradients; ++j)
						{
							UI8 ratio = readU8();
							COLOR color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
							fs.gradient[ratio] = color;
						}

						mFillstyleArray.push_back(fs);
					}
					break;

				default:
					assert("SWF shape fillstyle type not implemented" && false);
					break;
				}
			}
		}
		//-----------------------------------------------------------------------
		void SwfParser::parseLinestyleArray(const TagTypes& type)
		{
			UI16 linestyle_count = readU8();

			if(linestyle_count == 255)
			{
				linestyle_count = readU16();
			}

			// LINESTYLE ARRAY
			for(UI16 i=0; i<linestyle_count; ++i)
			{
				UI16 line_width = readU16();

				bool filled_line = false;
				if(type == TT_DefineShape4)
				{
					UI16 flags = readU16();

					if(((flags >> 12) & 3) == 2)
					{
						readU16(); // miter limit
					}

					if(flags & 8)
					{
						filled_line = true;
						VTX_WARN("Filled lines not yet supported");
					}
				}

				if(filled_line)
				{

				}
				else
				{
					LINESTYLE ls;
					ls.width = line_width;
					ls.color = readColor(type == TT_DefineShape3 || type == TT_DefineShape4);
					mLinestyleArray.push_back(ls);
				}
			}
		}
		//-----------------------------------------------------------------------
		void SwfParser::getFlashStyles()
		{
			ShapeElementList::iterator it = mShapeElements.begin();
			ShapeElementList::iterator end = mShapeElements.end();
			while(it != end)
			{
				const SHAPEELEMENT& se = *it;

				// store FILLSTYLE 0
				if(mFillstyles.find(se.fill0) == mFillstyles.end() && se.fill0 > 0)
				{
					const FILLSTYLE& fillstyle = mFillstyleArray.at(se.fill0 - 1);
					mFillstyles.insert(std::make_pair(se.fill0, fillstyle));
				}

				// store FILLSTYLE 1
				if(mFillstyles.find(se.fill1) == mFillstyles.end() && se.fill1 > 0)
				{
					const FILLSTYLE& fillstyle = mFillstyleArray.at(se.fill1 - 1);
					mFillstyles.insert(std::make_pair(se.fill1, fillstyle));
				}

				// store LINESTYLE
				if(mLinestyles.find(se.line) == mLinestyles.end() && se.line > 0)
				{
					const LINESTYLE& linestyle = mLinestyleArray.at(se.line - 1);
					mLinestyles.insert(std::make_pair(se.line, linestyle));
				}

				++it;
			}
		}
		//-----------------------------------------------------------------------
		void SwfParser::getFlashChunks()
		{
			uint count = 0;

			FillstyleMap::iterator fill_it = mFillstyles.begin();
			FillstyleMap::iterator fill_end = mFillstyles.end();
			while(fill_it != fill_end)
			{
				ContourElementList curr_chunk;

				// get and store the flash elements
				const SHAPEELEMENT* prev_elem = NULL;

				ShapeElementList::iterator elem_it = mShapeElements.begin();
				ShapeElementList::iterator elem_end = mShapeElements.end();
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

			ShapeElementList::iterator elem_it = mShapeElements.begin();
			ShapeElementList::iterator elem_end = mShapeElements.end();
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
		void SwfParser::generateSubshapes()
		{
			// loop through all fillstyles
			FillstyleMap::iterator fill_it = mFillstyles.begin();
			FillstyleMap::iterator fill_end = mFillstyles.end();
			for( ; fill_it != fill_end; ++fill_it)
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
				assert("There should be no elements left here" && !chunks.size());

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
			} // for END (fillstyles)
		}
		//-----------------------------------------------------------------------
		void SwfParser::generateSublines()
		{

		}
		//-----------------------------------------------------------------------
		void SwfParser::writeFillstyles(const UI16& shape_id)
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

				mCurrentFile->addResource(material);

				++it;
			}// while(fillstyles)
		}
		//-----------------------------------------------------------------------
		void SwfParser::writeSubshapes(const UI16& shape_id, ShapeResource* shape_resource)
		{
			SubShapeList::iterator subshape_it = mSubShapeList.begin();
			for( ; subshape_it != mSubShapeList.end(); ++subshape_it)
			{
				MaterialResource* mat = dynamic_cast<MaterialResource*>(
					mCurrentFile->getResource(StringHelper::toString(shape_id) + 
					"->" + StringHelper::toString((*subshape_it).fillstyle)));

				if(!mat)
				{
					VTX_EXCEPT("The requested Resource with the ID: %d is no MaterialResource.", (*subshape_it).fillstyle);
				}

				SubshapeResource* subshape = new SubshapeResource();
				subshape->setMaterial(mat);
				shape_resource->addSubshapeResource(subshape);

				ContourElementList::iterator element_it = (*subshape_it).elements.begin();
				for( ; element_it != (*subshape_it).elements.end(); ++element_it)
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
								SubshapeResource::ShapeElement shape_element;
								shape_element.type = SubshapeResource::ShapeElement::SID_MOVE_TO;
								shape_element.pos = Vector2(element.p0.x/20.0f, element.p0.y/20.0f);
								subshape->addShapeElement(shape_element);
							}

							SubshapeResource::ShapeElement shape_element;
							shape_element.type = SubshapeResource::ShapeElement::SID_LINE_TO;
							shape_element.pos = Vector2(element.p1.x/20.0f, element.p1.y/20.0f);

							subshape->addShapeElement(shape_element);
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
					}; // switch(element.type)
				} // for(elements)
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
		void SwfParser::debug_shape_element(const SubshapeResource::ShapeElement& element, FILE* file)
		{
#if defined DEBUG_FLASH_SHAPES && defined _DEBUG

			if(!FileHelper::doesDirectoryExist(DEBUG_OUTPUT_PATH))
				return;

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
	}
}
