/*
-----------------------------------------------------------------------------
This source file is part of "vektrix"
(the rich media and vector graphics rendering library)
For the latest info, see http://www.fuse-software.com/vektrix

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
#include <map>
#include <vector>

#include "vtxswfOriginalContourElement.h"

#include "vtxswfProcessFlashElements.h"


//-----------------------------------------------------------------------
//struct SubLine 
//{
//	// linestyle identifier (reference id)
//	unsigned int linestyle;
//
//	// number of contours to parse
//	unsigned int num_contours;
//
//	// list of contour elements
//	std::vector<ContourPoint> contours;
//};
//-----------------------------------------------------------------------

// list typedefs
//typedef std::map<unsigned int, FILLSTYLE*> FillstyleList;
//typedef std::map<unsigned int, LINESTYLE*> LinestyleList;
//typedef std::vector<SubLine> SubLineList;
//-----------------------------------------------------------------------

// the lists
OriginalElementList mOriginalElementList; // the original Flash elements
ChunkList mChunkList; // the original Flash elements
FillstyleList mFillstyleList; // the USED! fillstyles
LinestyleList mLinestyleList; // the USED! linestyles
SubShapeList mSubShapeList; // the sub-shapes
SubLineList mSubLineList; // the sub-lines
//-----------------------------------------------------------------------

// (pre-)processing
void process_flash_styles(SHAPE2 shape); // process the flash fill- and linestyles
void generate_chunks(void); // generate the chunks
void generate_subshapes(void); // generate the final subshapes
void generate_sublines(void); // generate the final sublines
//-----------------------------------------------------------------------

// writing to output file
void write_fillstyle(FILLSTYLE* fillstyle, unsigned int fillstyle_id, FILE* file); // write a fillstyle
void write_linestyle(LINESTYLE* linestyle, unsigned int linestyle_id, FILE* file); // write a linestyle
void write_subshape(const SubShape& subshape, FILE* file); // write a subshape
void write_subline(const SubLine& subline, FILE* file); // write a subline
//-----------------------------------------------------------------------

// main method
void handleShape(TAG* tag, FILE* file)
{
	// clear all lists
	mOriginalElementList.clear();
	mChunkList.clear();
	mFillstyleList.clear();
	mLinestyleList.clear();
	mSubShapeList.clear();
	mSubLineList.clear();

	// flash ID of the current shape
	int flash_id = swf_GetU16(tag);

	tag->pos = 0;
	tag->readBit = 0;

	// parse the shape from the given tag
	SHAPE2 shape;
	swf_ParseDefineShape(tag, &shape);

	// get the flash elements from swftools
	process_flash_elements(shape);

	// process the flash fill- and linestyles
	process_flash_styles(shape);

	// generate the chunks
	generate_chunks(); 

	// generate the subshapes
	generate_subshapes();

	// generate the sublines
	generate_sublines();

	printf("----------------\n");
	printf("writing SHAPE...\nID: %d\nfillstyles: %d (%d unused)\nlinestyles: %d (%d unused)\nshape-definitions: %d\nline-definitions: %d\n", 
		flash_id, 
		shape.numfillstyles, 
		shape.numfillstyles - mFillstyleList.size(), 
		shape.numlinestyles, 
		shape.numlinestyles - mLinestyleList.size(), 
		mSubShapeList.size(), 
		mSubLineList.size());
	printf("----------------\n");

	// write DEFINESHAPE tag
	unsigned int begin_shape = ogreSwf::OBOE::ID_DEFINESHAPE;
	fwrite(&begin_shape, sizeof(unsigned int), 1, file);

	// write Flash ID of the shape
	fwrite(&flash_id, sizeof(unsigned int), 1, file);

	fprintf(mLogFile, "Importing SHAPE -> id: %d\n", flash_id);

	fprintf(mLogFile, "bounds: {%d, %d, %d, %d}\n", shape.bbox->xmin, shape.bbox->ymin, shape.bbox->xmax, shape.bbox->ymax);

	// write bounding box information of the shape
	fwrite(&shape.bbox->xmin, sizeof(long), 1, file);
	fwrite(&shape.bbox->ymin, sizeof(long), 1, file);
	fwrite(&shape.bbox->xmax, sizeof(long), 1, file);
	fwrite(&shape.bbox->ymax, sizeof(long), 1, file);

	//--------------------
	// write FILLSTYLES
	//--------------------

	// write the count of fillstyles included in the shape (without unused ones!)
	unsigned int fillstyles_count = mFillstyleList.size();
	fwrite(&fillstyles_count, sizeof(unsigned int), 1, file);

	// write all fillstyles
	// they were pre-processed and are waiting in the FillstyleList
	for(FillstyleList::iterator it = mFillstyleList.begin(); 
		it!=mFillstyleList.end(); 
		it++)
	{
		write_fillstyle(it->second, it->first, file);
	}

	//--------------------
	// write LINESTYLES
	//--------------------

	// write the count of linestyles included in the shape (without unused ones!)
	unsigned int linestyles_count = mLinestyleList.size();
	fwrite(&linestyles_count, sizeof(unsigned int), 1, file);

	// write all linestyles
	// they were pre-processed and are waiting in the LinestyleList
	for(LinestyleList::iterator it = mLinestyleList.begin(); 
		it != mLinestyleList.end(); 
		it++)
	{
		write_linestyle(it->second, it->first, file);
	}

	//---------------------------
	// write the SUBSHAPE-DATA
	//---------------------------

	// write the count of subshapes included in the shape
	unsigned int subshapes_count = mSubShapeList.size();
	fwrite(&subshapes_count, sizeof(unsigned int), 1, file);

	// write all subshapes
	// they were pre-processed and are waiting in the SubShapeList
	for(SubShapeList::iterator it = mSubShapeList.begin(); 
		it != mSubShapeList.end(); 
		it++)
	{
		write_subshape(*it, file);
	}

	//--------------------------
	// write the SUBLINE-DATA
	//--------------------------

	// write the count of sublines included in the shape
	unsigned int sublines_count = mSubLineList.size();
	fwrite(&sublines_count, sizeof(unsigned int), 1, file);

	// write all sublines
	// they were pre-processed and are waiting in the SubLineList
	for(SubLineList::iterator it = mSubLineList.begin(); 
		it != mSubLineList.end(); 
		it++)
	{
		write_subline(*it, file);
	}
}

//-----------------------------------------------------------------------

// process the flash fill- and linestyles
void process_flash_styles(SHAPE2 shape)
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
}
//-----------------------------------------------------------------------

// generate the chunks
void generate_chunks(void)
{
	// loop through all fillstyles
	for(FillstyleList::iterator fill_it = mFillstyleList.begin(); 
		fill_it != mFillstyleList.end(); 
		fill_it++)
	{
		// the current chunk
		ContourChunk* chunk = NULL;

		// the "new chunk" flag
		bool is_new_chunk = true;

		// loop through all elements
		for(unsigned int i = 0; i < mOriginalElementList.size(); i++)
		{
			// the current element
			OriginalContourElement element = mOriginalElementList.at(i);

			// the element uses the fillstyle that we are "filtering" for
			if(element.fillstyle0 == fill_it->first || element.fillstyle1 == fill_it->first)
			{
				// start a new chunk
				if(is_new_chunk || element.type == ogreSwf::OBOE::CID_BEGIN)
				{
					chunk = new ContourChunk(fill_it->first);
					is_new_chunk = false;

					// store the current chunk
					mChunkList.push_back(chunk);

					// store the previous element too
					if(element.type == ogreSwf::OBOE::CID_LINE || element.type == ogreSwf::OBOE::CID_BEZIER)
					{
						// only if there IS! a previous element
						if(i > 0)
						{
							// (!!!gets converted to ContourPoint!!!)
							chunk->addElement(mOriginalElementList.at(i-1), true);
						}
					}

					// exchange "moveTo" elements by "lineTo"
					if(element.type == ogreSwf::OBOE::CID_BEGIN)
					{
						element.type = ogreSwf::OBOE::CID_LINE;
					}
				}

				// store the current element (!!!gets converted to ContourPoint!!!)
				chunk->addElement(element);
			}
			// the fillstyle is different --> set the flag to start a new chunk
			else
			{
				is_new_chunk = true;
			}
		}
	} // for END (fillstyles)

	// DEBUG the chunks
	for(FillstyleList::iterator fill_it = mFillstyleList.begin(); 
		fill_it != mFillstyleList.end(); 
		fill_it++)
	{
		char filename[128];
		sprintf_s(filename, "C:/swfs/chunk_%d.txt", fill_it->first);
		FILE* file = fopen(filename, "w");

		for(ChunkList::iterator chunk_it = mChunkList.begin(); 
			chunk_it != mChunkList.end(); 
			chunk_it++)
		{
			if((*chunk_it)->fillstyle == fill_it->first)
			{
				fprintf(file, "NEW CHUNK\n");

				for(NewElementList::iterator elem_it = (*chunk_it)->mNewContourElements.begin(); 
					elem_it != (*chunk_it)->mNewContourElements.end(); 
					elem_it++)
				{
					if((*elem_it).type == ogreSwf::OBOE::CID_BEZIER)
					{
						fprintf(file, "%4.2f %4.2f (S)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_CONTROL_POINT)
					{
						fprintf(file, "%4.2f %4.2f (C)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_LINE)
					{
						fprintf(file, "%4.2f %4.2f (L)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_BEGIN)
					{
						fprintf(file, "(BEGIN)\n");
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_END)
					{
						fprintf(file, "(END)\n");
					}
				}

				fprintf(file, "CHUNK END\n\n");
			}
		}

		fclose(file);
	}

	//            /
	//           /
	//          /
	//         /
	//     \  /
	//      \/
}
//-----------------------------------------------------------------------

// generate the final subshapes
void generate_subshapes(void)
{
	// loop through all fillstyles
	for(FillstyleList::iterator fill_it = mFillstyleList.begin(); 
		fill_it != mFillstyleList.end(); 
		fill_it++)
	{
		SubShape temp_subshape;
		temp_subshape.fillstyle = fill_it->first;

		// the previously processed chunk (set to NULL if a contour is finished)
		ContourChunk* start_chunk = NULL;
		ContourChunk* prev_chunk = NULL;

		for(int i = 0; i < mChunkList.size(); i++)
		{
			// the current chunk
			ContourChunk* curr_chunk = mChunkList.at(i);

			// the chunk has the fillstyle we are searching for AND is not yet used
			if(fill_it->first == curr_chunk->fillstyle && !curr_chunk->isUsed())
			{
				// this is a new contour
				if(prev_chunk == NULL)
				{
					// add a stand-alone chunk
					if(curr_chunk->isClosed())
					{
						// begin a new contour
						temp_subshape.beginContour();

						// add ONLY this chunk
						temp_subshape.addChunk(curr_chunk);
						curr_chunk->touch();

						// end the contour
						temp_subshape.endContour();

						prev_chunk = NULL;
						start_chunk = NULL;

						i = -1; // restart at first chunk
					}
					// start a new contour
					else
					{
						// begin a new contour
						temp_subshape.beginContour();

						// add this chunk
						temp_subshape.addChunk(curr_chunk);
						curr_chunk->touch();

						prev_chunk = curr_chunk;
						start_chunk = curr_chunk;

						i = -1; // restart at first chunk
					}
				}
				// continue the current contour
				else
				{
					if(curr_chunk->isConnectedWith(prev_chunk))
					{
						if(start_chunk->isEndingChunk(curr_chunk))
						{
							// add this chunk
							temp_subshape.addChunk(curr_chunk);
							curr_chunk->touch();

							// end the contour
							temp_subshape.endContour();

							prev_chunk = NULL;
							start_chunk = NULL;
						}
						else
						{
							// add this chunk
							temp_subshape.addChunk(curr_chunk);
							curr_chunk->touch();

							prev_chunk = curr_chunk;
						}

						i = -1; // restart at first chunk
					}
				}
			}
		}

		// store the result
		temp_subshape.num_contours = temp_subshape.contours.size();
		mSubShapeList.push_back(temp_subshape);
	} // for END (fillstyles)

	// DEBUG the contours
	for(FillstyleList::iterator fill_it = mFillstyleList.begin(); 
		fill_it != mFillstyleList.end(); 
		fill_it++)
	{
		char filename[128];
		sprintf_s(filename, "C:/swfs/contour_%d.txt", fill_it->first);
		FILE* file = fopen(filename, "w");

		for(SubShapeList::iterator subshape_it = mSubShapeList.begin(); 
			subshape_it != mSubShapeList.end(); 
			subshape_it++)
		{
			if((*subshape_it).fillstyle == fill_it->first)
			{
				for(NewElementList::iterator elem_it = (*subshape_it).contours.begin(); 
					elem_it != (*subshape_it).contours.end(); 
					elem_it++)
				{
					if((*elem_it).type == ogreSwf::OBOE::CID_BEGIN)
					{
						fprintf(file, "CID_BEGIN\n");
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_END)
					{
						fprintf(file, "CID_END\n\n");
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_LINE)
					{
						fprintf(file, "%4.2f %4.2f (l)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_CONTROL_POINT)
					{
						fprintf(file, "%4.2f %4.2f (C)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
					else if((*elem_it).type == ogreSwf::OBOE::CID_BEZIER)
					{
						fprintf(file, "%4.2f %4.2f (S)\n", (*elem_it).point[0] / 20.0f, (*elem_it).point[1] / 20.0f);
					}
				}
			}
		}

		fclose(file);
	}

	//            /
	//           /
	//          /
	//         /
	//     \  /
	//      \/
}
//-----------------------------------------------------------------------

// generate the final sublines
void generate_sublines(void)
{

}
//-----------------------------------------------------------------------

// write the given fillstyle to the output file
void write_fillstyle(FILLSTYLE* fillstyle, unsigned int fillstyle_id, FILE* file)
{
	// write the Flash ID of the fillstyle
	fwrite(&fillstyle_id, sizeof(unsigned int), 1, file);

	switch(fillstyle->type)
	{
	case 0x00: //color
		{
			// is the fillstyle ever used? DEPRECATED?!!
			if(mFillstyleList.find(fillstyle_id) == mFillstyleList.end())
			{
				//printf("*)fillstyle %d: [unused]\n\n", fillstyle_id);
				return;
			}

			// write FST_COLOR tag
			unsigned int type = ogreSwf::OBOE::FST_COLOR;
			fwrite(&type, sizeof(unsigned int), 1, file);

			//write RGBA values of the fillstyle
			unsigned int rgba[4] = {fillstyle->color.r, fillstyle->color.g, fillstyle->color.b, fillstyle->color.a};
			fwrite(&rgba, sizeof(unsigned int[4]), 1, file);

			fprintf(mLogFile, "FILLSTYLE: %d -> COLOR: %d, %d, %d, %d\n", fillstyle_id, fillstyle->color.r, fillstyle->color.g, fillstyle->color.b, fillstyle->color.a);

			return;
		}
		break;
	case 0x10: case 0x12: //gradient
		{
			// is the fillstyle ever used? DEPRECATED?!!
			if(mFillstyleList.find(fillstyle_id) == mFillstyleList.end())
			{
				//printf("*)fillstyle %d: [unused]\n\n", fillstyle_id);
				return;
			}

			printf("*)fillstyle %d:\n", fillstyle_id);
			printf("	gradient: %d steps\n", fillstyle->gradient.num);

			for(int i=0; i<fillstyle->gradient.num; i++)
				printf("	 step:\n	  rgba/ratio: %d, %d, %d, %d / %d\n", 
				fillstyle->gradient.rgba[i].r, 
				fillstyle->gradient.rgba[i].g, 
				fillstyle->gradient.rgba[i].b, 
				fillstyle->gradient.rgba[i].a, 
				fillstyle->gradient.ratios[i] 
				);
			printf("\n\n");

			// write FST_GRADIENT tag
			unsigned int type = ogreSwf::OBOE::FST_GRADIENT;
			fwrite(&type, sizeof(unsigned int), 1, file);

			return;
		}
		break;
	case 0x40: //bitmap
		{
			// is the fillstyle ever used? DEPRECATED?!!
			if(mFillstyleList.find(fillstyle_id) == mFillstyleList.end())
			{
				//printf("*)fillstyle %d: [unused]\n\n", fillstyle_id);
				return;
			}

			// hackish, but works ;)
			if(fillstyle->id_bitmap > 50000)
			{
				printf("*)fillstyle %d: [out of range]\n\n", fillstyle_id);
				return;
			}

			//printf("*)fillstyle %d:\n", fillstyle_id);
			//printf("	image_id: %d\n", style->id_bitmap);
			////printf("	r0/1: %4.2lf / %4.2lf\n", style->m.r0, style->m.r1);
			////printf("	sx/y: %4.2lf / %4.2lf\n", style->m.sx, style->m.sy);
			////printf("	tx/y: %4.2lf / %4.2lf\n\n", style->m.tx, style->m.ty);

			// write FST_BITMAP tag
			unsigned int type = ogreSwf::OBOE::FST_BITMAP;
			fwrite(&type, sizeof(unsigned int), 1, file);

			// write the Flash ID of the used bitmap/image
			unsigned int img_id = fillstyle->id_bitmap;
			fwrite(&img_id, sizeof(unsigned int), 1, file);

			return;
		}
		break;
	case 0x41: //bitmap
		{
			// is the fillstyle ever used? DEPRECATED?!!
			if(mFillstyleList.find(fillstyle_id) == mFillstyleList.end())
			{
				//printf("*)fillstyle %d: [unused]\n\n", fillstyle_id);
				return;
			}

			// hackish, but works ;)
			if(fillstyle->id_bitmap > 50000)
			{
				printf("*)fillstyle %d: [out of range]\n\n", fillstyle_id);
				return;
			}

			// write FST_BITMAP tag
			unsigned int type = ogreSwf::OBOE::FST_BITMAP;
			fwrite(&type, sizeof(unsigned int), 1, file);

			// write the Flash ID of the used bitmap/image
			unsigned int img_id = fillstyle->id_bitmap;
			fwrite(&img_id, sizeof(unsigned int), 1, file);

			return;
		}
		break;
	default: // unknown
		{
			printf("UNKNOWN[%02x]\n",fillstyle->type);
		}
		break;
	};
}
//-----------------------------------------------------------------------

// write the given linestyle to the output file
void write_linestyle(LINESTYLE* linestyle, unsigned int linestyle_id, FILE* file)
{
	// is the fillstyle ever used? DEPRECATED?!!
	if(mLinestyleList.find(linestyle_id) == mLinestyleList.end())
	{
		//printf("*)linestyle %d: [unused]\n\n", linestyle_id);
		return;
	}

	//// write Flash ID of the linestyle
	//fwrite(&linestyle_id, sizeof(unsigned int), 1, file);

	//// write thickness of the linestyle
	//unsigned int thickness = linestyle->width;
	//fwrite(&thickness, sizeof(unsigned int), 1, file);

	//// write RGBA values of the linestyle
	//unsigned int rgba[4] = {linestyle->color.r, linestyle->color.g, linestyle->color.b, linestyle->color.a};
	//fwrite(&rgba, sizeof(unsigned int[4]), 1, file);
}
//-----------------------------------------------------------------------

// write the given subshape to the output file
void write_subshape(const SubShape& subshape, FILE* file)
{
	// write the fillstyle ID
	fwrite(&subshape.fillstyle, sizeof(unsigned int), 1, file);

	// write the number of contours to parse
	fwrite(&subshape.num_contours, sizeof(unsigned int), 1, file);

	for(unsigned int i=0; i<subshape.num_contours; i++)
	{
		// the current element
		ContourPoint element = subshape.contours.at(i);

		// of what type is it?
		switch(element.type)
		{
		case ogreSwf::OBOE::CID_BEGIN:
			{
				// write the CID_BEGIN tag only!
				fwrite(&element.type, sizeof(unsigned int), 1, file);
			}
			break;
		case ogreSwf::OBOE::CID_LINE:
			{
				// write the CID_LINE tag
				fwrite(&element.type, sizeof(unsigned int), 1, file);

				// write the current position
				fwrite(&element.point, sizeof(long[2]), 1, file);
			}
			break;
		case ogreSwf::OBOE::CID_BEZIER:
			{
				// write the current position
				fwrite(&element.point, sizeof(long[2]), 1, file);
			}
			break;
		case ogreSwf::OBOE::CID_CONTROL_POINT:
			{
				// write the CID_CONTROL_POINT tag
				unsigned int temp_type = ogreSwf::OBOE::CID_BEZIER;
				fwrite(&temp_type, sizeof(unsigned int), 1, file);

				// write the current position
				fwrite(&element.point, sizeof(long[2]), 1, file);
			}
			break;
		case ogreSwf::OBOE::CID_END:
			{
				// write the CID_END tag only!
				fwrite(&element.type, sizeof(unsigned int), 1, file);
			}
			break;
		};
	}
}
//-----------------------------------------------------------------------

// write the given subline to the output file
void write_subline(const SubLine& subline, FILE* file)
{

}
//-----------------------------------------------------------------------
