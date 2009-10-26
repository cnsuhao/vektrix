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
#include "oboe_defines.h"

U8* jpegtables = 0;
int jpegtablessize;

void handlejpegtables(TAG* tag);
int findjpegboundary(U8* data, int len);

void handlejpeg(TAG* tag, FILE* file)
{
	unsigned int def = ogreSwf::OBOE::ID_DEFINEJPEG;
	unsigned long len = -1;
    
    int id = GET16(tag->data);

    /* swf jpeg images have two streams, which both start with ff d8 and
       end with ff d9. The following code handles sorting the middle
       <ff d9 ff d8> bytes out, so that one stream remains */

	fwrite(&def, sizeof(unsigned int), 1, file);
	fwrite(&id, sizeof(unsigned int), 1, file);

    if(tag->id == ST_DEFINEBITSJPEG && tag->len>2 && jpegtables)
	{
		len = jpegtablessize-2+tag->len-2-2;

		printf("----------------\n");
		printf("writing JPEG...\nID: %d\nsize: %d bytes\n", id, len);
		fwrite(&len, sizeof(unsigned long), 1, file);
		fwrite(jpegtables, 1, jpegtablessize-2, file); //don't write end tag (ff,d8)
		fwrite(&tag->data[2+2], tag->len-2-2, 1, file); //don't write start tag (ff,d9)
    }
    else if(tag->id == ST_DEFINEBITSJPEG2 && tag->len>2)
	{
		int end = tag->len;
		int pos = findjpegboundary(&tag->data[2], tag->len-2);

		if(pos>=0)
		{
			pos+=2;
			len = pos-2+end-(pos+4);

			printf("----------------\n");
			printf("writing JPEG...\nID: %d\nsize: %d bytes\n", id, len);
			fwrite(&len, sizeof(unsigned long), 1, file);
			fwrite(&tag->data[2], pos-2, 1, file);
			fwrite(&tag->data[pos+4], end-(pos+4), 1, file);
		}
		else
		{
			len = end-2;

			printf("----------------\n");
			printf("writing JPEG...\nID: %d\nsize: %d bytes\n", id, len);
			fwrite(&len, sizeof(unsigned long), 1, file);
			fwrite(&tag->data[2], end-2, 1, file);
		}
	}
    else if(tag->id == ST_DEFINEBITSJPEG3 && tag->len>6)
	{
		U32 end = GET32(&tag->data[2])+6;
		int pos = findjpegboundary(&tag->data[6], tag->len-6);

		if(pos < 0)
			return;

		pos+=6;
		len = pos-6+end-(pos+4);

		printf("----------------\n");
		printf("writing JPEG...\nID: %d\nsize: %d bytes\n", id, len);
		fwrite(&len, sizeof(unsigned long), 1, file);
		fwrite(&tag->data[6], pos-6, 1, file);
		fwrite(&tag->data[pos+4], end-(pos+4), 1, file);
	}

	printf("----------------\n\n");
}

void handlejpegtables(TAG* tag)
{
	if(tag->id == ST_JPEGTABLES)
	{
		jpegtables = tag->data;
		jpegtablessize = tag->len;
	}
}

int findjpegboundary(U8* data, int len)
{
    int t;
    int pos=-1;
    for(t=0;t<len;t++)
	{
		if(data[t  ]==0xff && 
			data[t+1]==0xd9 && 
			data[t+2]==0xff && 
			data[t+3]==0xd8)
		{
			pos = t;
		}
    }
    return pos;
}
