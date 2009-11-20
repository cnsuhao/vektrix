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
char* videostream_data = 0;
unsigned long videostream_len = 0;

void handlevideostream(TAG* tag)
{
	//resize the buffer
	videostream_data = (char*)realloc(videostream_data, videostream_len + tag->len);
	//copy the new soundstream chunk to the buffer
	memcpy(videostream_data + videostream_len, tag->data, tag->len);
	//increase the size variable
	videostream_len += tag->len;
}
