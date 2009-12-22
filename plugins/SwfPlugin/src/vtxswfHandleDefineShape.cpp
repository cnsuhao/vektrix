#include "vtxswfParser2.h"

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
		void SwfParser2::handleDefineShape()
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

			ShapeResource* shape_resource = new ShapeResource(StringHelper::toString(shape_id));
			mCurrentFile->addResource(shape_resource);

			BoundingBox box(
				Vector2(bounds.xmin/20.0f, bounds.ymin/20.0f), 
				Vector2(bounds.xmax/20.0f, bounds.ymax/20.0f));

			shape_resource->setBoundingBox(box);

			UI16 fillstyle_count = readU8();

			if(fillstyle_count == 255)
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
						fs.color = readColor();
						fs.type = FST_Solid;
						mFillstyleArray.push_back(fs);
					}
					break;

				default:
					VTX_WARN("SWF shape fillstyle type not implemented: %d", fill_type);
					break;
				}
			}

			UI16 linestyle_count = readU8();

			if(linestyle_count == 255)
			{
				linestyle_count = readU16();
			}

			// LINESTYLE ARRAY
			for(UI16 i=0; i<linestyle_count; ++i)
			{
				UI16 line_width = readU16();
				COLOR color = readColor();
			}

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
				SHAPEELEMENT se;
				se.cx = se.cy = 0;

				UI8 flags = readUBits(1);
				// edge record
				if(flags)
				{
					flags = readUBits(1);
					// straight edge
					if(flags)
					{
						se.type = SET_LINE;

						UI8 num_bits = readUBits(4) + 2;
						UI8 line_flags = readUBits(2);

						// general line or vertical line
						if(line_flags & 2 || !(line_flags & 1))
						{
							x += readSBits(num_bits); // delta x
						}
						// general line or horizontal line
						if(line_flags & 2 || line_flags & 1)
						{
							y += readSBits(num_bits); // delta y
						}
					}
					// curved edge
					else
					{
						se.type = SET_BEZIER;

						UI8 num_bits = readUBits(4) + 2;

						x += readSBits(num_bits); // delta x
						y += readSBits(num_bits); // delta y

						se.cx = x;
						se.cy = y;

						x += readSBits(num_bits); // delta x
						y += readSBits(num_bits); // delta y
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
						se.type = SET_MOVE;

						UI8 num_move_bits = readUBits(5);
						x = readSBits(num_move_bits);
						y = readSBits(num_move_bits);
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
					if(flags & 16)
					{
						assert(false && "new styles not yet implemented");
						// TODO: readFillStyleArray
						// TODO: readLineStyleArray
						num_fill_bits = readUBits(4);
						num_line_bits = readUBits(4);
					}
				}

				se.x = x;
				se.y = y;
				se.fill0 = fillstyle0;
				se.fill1 = fillstyle1;
				se.line = linestyle;

				mShapeElements.push_back(se);

				std::cout << "[" << fillstyle0 << "|" << fillstyle1 << "]{" << linestyle << "} X: " << x << ", Y: " << y << std::endl;
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
		void SwfParser2::getFlashStyles()
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
		void SwfParser2::getFlashChunks()
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
									elem.p0.y = -prev_elem->y;

									elem.p1.x = se.x;
									elem.p1.y = -se.y;

									curr_chunk.push_back(elem);
									++count;
								}
								break;

							case SET_BEZIER:
								{
									ContourElement elem;
									elem.type = CID_BEZIER;

									elem.p0.x = prev_elem->x;
									elem.p0.y = -prev_elem->y;

									elem.ctrl.x = se.cx;
									elem.ctrl.y = -se.cy;

									elem.p1.x = se.x;
									elem.p1.y = -se.y;

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

#ifdef DEBUG_FLASH_SHAPES
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
		void SwfParser2::generateSubshapes()
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
					debug_contour_element(*elem_it, file);
					++elem_it;
				}

				fclose(file);

#endif

				// store the result
				mSubShapeList.push_back(subshape);
			} // for END (fillstyles)
		}
		//-----------------------------------------------------------------------
		void SwfParser2::generateSublines()
		{

		}
		//-----------------------------------------------------------------------
		void SwfParser2::writeFillstyles(const UI16& shape_id)
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
		void SwfParser2::writeSubshapes(const UI16& shape_id, ShapeResource* shape_resource)
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
		void SwfParser2::debug_contour_element(const ContourElement& element, FILE* file)
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
		void SwfParser2::debug_shape_element(const SubshapeResource::ShapeElement& element, FILE* file)
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
	}
}
