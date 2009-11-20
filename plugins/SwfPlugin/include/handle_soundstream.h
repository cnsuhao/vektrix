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
char* soundstream_data = 0;
unsigned long soundstream_len = 0;

void handlesoundstream(TAG* tag)
{
	switch(tag->id)
	{
	case ST_SOUNDSTREAMHEAD:
		if((tag->data[1]&0x30) == 0x20)//mp3 compression
		{
			//mp3file = fopen(filename, "wb");
			//msg("<notice> Writing mp3 data to %s",filename);
		}
	    else
		{
			printf("can't write unknown sound stream format\n\n");
			return;
		}
		break;

	case ST_SOUNDSTREAMHEAD2:
		if((tag->data[1]&0x30) == 0x20)//mp3 compression
		{
			//mp3file = fopen(filename, "wb");
			//msg("<notice> Writing mp3 data to %s",filename);
	    }
	    else
		{
			printf("can't write unknown sound stream format\n\n");
			return;
		}
		break;

	case ST_SOUNDSTREAMBLOCK:
		{
			//resize the buffer
			soundstream_data = (char*)realloc(soundstream_data, soundstream_len + tag->len-4);
			//copy the new soundstream chunk to the buffer
			memcpy(soundstream_data + soundstream_len, &tag->data[4], tag->len-4);
			//increase the size variable
			soundstream_len += tag->len-4;
		}
		break;
	}
}
