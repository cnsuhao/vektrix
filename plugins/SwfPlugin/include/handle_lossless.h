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
unsigned long size_storage = 0;
U32 mycrc32;
U32* crc32_table = 0;

void make_crc32_table();
void png_write_byte(FILE* fi, U8 byte);
void png_write_dword(FILE* fi, U32 dword);
void png_start_chunk(FILE* fi, char*type, int len);
void png_write_bytes(FILE* fi, U8*bytes, int len);
void png_end_chunk(FILE* fi);

void handlelossless(TAG* tag, FILE* file)
{
	int width, height;
	//int crc;
	int id;
	int t;
	U8 bpp = 1;
	U8 format;
	//U8 tmp;
	U8* data=0;
	U8* data2=0;
	U8* data3=0;
	U32 datalen;
	U32 datalen2;
	U32 datalen3;
	U8 head[] = {137,80,78,71,13,10,26,10};
	int cols;
	char alpha = tag->id == ST_DEFINEBITSLOSSLESS2;
	RGBA* palette;
	int pos;
	int error;
	//U32 tmp32;
	//ogreSwf
	unsigned int def = ogreSwf::OBOE::ID_DEFINEPNG;
	unsigned long len = -1;
	fpos_t lenPos;
	fpos_t endPos;

	size_storage = 0;

	make_crc32_table();

	if(tag->id != ST_DEFINEBITSLOSSLESS &&
		tag->id != ST_DEFINEBITSLOSSLESS2)
	{
		int id = GET16(tag->data);
		fprintf(stderr, "Object %d is not a PNG picture!\n",id);
		exit(1);
	}

	id = swf_GetU16(tag);
	format = swf_GetU8(tag);
	if(format == 3) bpp = 8;
	if(format == 4) bpp = 16;
	if(format == 5) bpp = 32;
	if(format!=3 && format!=5)
	{
		if(format == 4)
			fprintf(stderr, "Can't handle 16-bit palette images yet (image %d)\n",id);
		else 
			fprintf(stderr, "Unknown image type %d in image %d\n", format, id);
		return;
	}

	width = swf_GetU16(tag);
	height = swf_GetU16(tag);

	if(format == 3)
		cols = swf_GetU8(tag) + 1;
	// this is what format means according to the flash specification. (which is
	// clearly wrong)
	//    if(format == 4) cols = swf_GetU16(tag) + 1;
	//    if(format == 5) cols = swf_GetU32(tag) + 1;
	else cols = 0;

	//msg("<verbose> Width %d", width);
	//msg("<verbose> Height %d", height);
	//msg("<verbose> Format %d", format);
	//msg("<verbose> Cols %d", cols);
	//msg("<verbose> Bpp %d", bpp);

	datalen = (width*height*bpp/8+cols*8);
	do
	{
		if(data)
			free(data);

		datalen+=4096;
		data = (U8*)malloc(datalen);
		error = uncompress (data, &datalen, &tag->data[tag->pos], tag->len-tag->pos);
	}while(error == Z_BUF_ERROR);

	if(error != Z_OK)
	{
		fprintf(stderr, "Zlib error %d (image %d)\n", error, id);
		return;
	}
	//msg("<verbose> Uncompressed image is %d bytes (%d colormap)", datalen, (3+alpha)*cols);
	pos = 0;
	datalen2 = datalen;
	data2 = (U8*)malloc(datalen2);
	palette = (RGBA*)malloc(cols*sizeof(RGBA));

	for(t=0;t<cols;t++)
	{
		palette[t].r = data[pos++];
		palette[t].g = data[pos++];
		palette[t].b = data[pos++];
		if(alpha)
		{
			palette[t].a = data[pos++];
		}
	}

	fwrite(&def, sizeof(unsigned int), 1, file);
	fwrite(&id, sizeof(unsigned int), 1, file);

	//store position of "len" byte
	fgetpos(file, &lenPos);

	len = 0; //set "len" to 0, we will overwrite this afterwards with "size_storage"
	fwrite(&len, sizeof(unsigned long), 1, file);

	fwrite(head,sizeof(head),1,file);
	//store size of head
	size_storage += sizeof(head);

	png_start_chunk(file, "IHDR", 13);
	png_write_dword(file,width);
	png_write_dword(file,height);
	png_write_byte(file,8);

	if(format == 3)
		png_write_byte(file,3); //indexed
	else if(format == 5 && alpha == 0)
		png_write_byte(file,2); //rgb
	else if(format == 5 && alpha == 1)
		png_write_byte(file,6); //rgba
	else return;

	png_write_byte(file,0); //compression mode
	png_write_byte(file,0); //filter mode
	png_write_byte(file,0); //interlace mode
	png_end_chunk(file);

	if(format == 3)
	{
		png_start_chunk(file, "PLTE", 768);

		for(t=0;t<256;t++)
		{
			png_write_byte(file,palette[t].r);
			png_write_byte(file,palette[t].g);
			png_write_byte(file,palette[t].b);
		}
		png_end_chunk(file);

		if(alpha)
		{
			/* write alpha palette */
			png_start_chunk(file, "tRNS", 256);

			for(t=0;t<256;t++)
			{
				png_write_byte(file,palette[t].a);
			}
			png_end_chunk(file);
		}
	}

	{
		int pos2 = 0;
		int x,y;
		int srcwidth = width * (bpp/8);
		datalen3 = (width*4+5)*height;
		data3 = (U8*)malloc(datalen3);

		for(y=0; y<height; y++)
		{
			data3[pos2++]=0; //filter type

			if(bpp==32)
			{
				if(!alpha)
				{
					// 32 bit to 24 bit "conversion"
					for(x=0;x<width;x++)
					{
						data3[pos2++]=data[pos+1];
						data3[pos2++]=data[pos+2];
						data3[pos2++]=data[pos+3];
						pos+=4; //ignore padding byte
					}
				}
				else
				{
					for(x=0;x<width;x++)
					{
						data3[pos2++]=data[pos+1];
						data3[pos2++]=data[pos+2];
						data3[pos2++]=data[pos+3];
						data3[pos2++]=data[pos+0]; //alpha
						pos+=4;
					}
				}
			}
			else {
				for(x=0;x<srcwidth;x++)
					data3[pos2++]=data[pos++];
			}

			pos+=((srcwidth+3)&~3)-srcwidth; //align
		}
		datalen3=pos2;
	}

	if(compress (data2, &datalen2, data3, datalen3) != Z_OK)
	{
		fprintf(stderr, "zlib error in pic %d\n", id);
		return;
	}
	//msg("<verbose> Compressed data is %d bytes", datalen2);
	png_start_chunk(file, "IDAT", datalen2);
	png_write_bytes(file,data2,datalen2);
	png_end_chunk(file);
	png_start_chunk(file, "IEND", 0);
	png_end_chunk(file);

	//store end position
	fgetpos(file, &endPos);
	//go to len position
	fsetpos(file, &lenPos);
	//write the length
	fwrite(&size_storage, sizeof(unsigned long), 1, file);
	//go to end position again
	fsetpos(file, &endPos);

	printf("----------------\n");
	printf("writing PNG...\nID: %d\nsize: %d bytes\n", id, size_storage);
	printf("----------------\n\n");

	free(data);
	free(data2);
	free(data3);
}

void make_crc32_table()
{
	int t;

	if(crc32_table) 
		return;

	crc32_table = (U32*)malloc(1024);

	for (t = 0; t < 256; t++)
	{
		U32 c = t;
		int s;

		for (s = 0; s < 8; s++)
		{
			c = (0xedb88320L*(c&1)) ^ (c >> 1);
		}

		crc32_table[t] = c;
	}
}

void png_write_byte(FILE* fi, U8 byte)
{
	//increase size_storage about 1
	size_storage += 1;
	fwrite(&byte,1,1,fi);
	mycrc32 = crc32_table[(mycrc32 ^ byte) & 0xff] ^ (mycrc32 >> 8);
}

void png_write_dword(FILE* fi, U32 dword)
{
	png_write_byte(fi,dword>>24);
	png_write_byte(fi,dword>>16);
	png_write_byte(fi,dword>>8);
	png_write_byte(fi,dword);
}

void png_start_chunk(FILE* fi, char*type, int len)
{
	U8 mytype[4]={0,0,0,0};
	U32 mylen = REVERSESWAP32(len);
	memcpy(mytype,type,strlen(type));
	//increase size_storage about 4
	size_storage += 4;
	fwrite(&mylen, 4, 1, fi);
	mycrc32=0xffffffff;
	png_write_byte(fi,mytype[0]);
	png_write_byte(fi,mytype[1]);
	png_write_byte(fi,mytype[2]);
	png_write_byte(fi,mytype[3]);
}

void png_write_bytes(FILE* fi, U8*bytes, int len)
{
	int t;
	for(t=0;t<len;t++)
		png_write_byte(fi,bytes[t]);
}

void png_end_chunk(FILE* fi)
{
	U32 tmp = REVERSESWAP32((mycrc32^0xffffffff));
	//increase size_storage about 4
	size_storage += 4;
	fwrite(&tmp,4,1,fi);
}