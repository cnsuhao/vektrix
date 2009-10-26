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
void handledefinesound(TAG* tag, FILE* file)
{
	unsigned int def;
	unsigned long len;
	U8 flags;
	U32 samples;
	char*extension = 0;
	int format;
	U16 id;
	bool stereo;
	char* rates[] = {"5500","11025","22050","44100"};
	id = swf_GetU16(tag); //id

    flags = swf_GetU8(tag);
    format = flags>>4;
    unsigned int samplerate = (flags>>2)&3;
    unsigned int bitrate = flags&2?16:8;
    stereo = flags&1;
    
    samples = swf_GetU32(tag);

    extension = "raw";

	def = ogreSwf::OBOE::ID_DEFINESOUND;

	if(format == 2) // MP3
	{
		swf_GetU16(tag); //numsamples_seek
		len = tag->len - tag->pos;
		printf("writing MP3...\nID: %d\nsample-rate: %s\nbit-rate: %d\nstereo: %s\nsize: %d bytes\n\n", id, rates[samplerate], bitrate, stereo?"yes":"no", len);
		extension = "mp3";
	}
	else if(format == 0) // RAW
	{
		len = tag->len - tag->pos;
		printf("writing RAW...\nID: %d\nsample-rate: %s\nbit-rate: %d\nstereo: %s\nsize: %d bytes\n\n", id, rates[samplerate], bitrate, stereo?"yes":"no", len);
		// TODO: convert to WAV
		extension = "raw";
	}
	else if(format == 1) // adpcm
	{
		len = tag->len - tag->pos;
		printf("writing ADPCM...\nID: %d\nsample-rate: %s\nbit-rate: %d\nstereo: %s\nsize: %d bytes\n\n", id, rates[samplerate], bitrate, stereo?"yes":"no", len);
		extension = "adpcm";
	}
	else
	{
		printf("can't write unknown sound format: %d\n\n", format);
		return;
	}

	// write ID_DEFINESOUND
	fwrite(&def, sizeof(unsigned int), 1, file);

	// write the id of the sound
	fwrite(&id, sizeof(unsigned int), 1, file);

	// write the format of the sound
	fwrite(&format, sizeof(unsigned int), 1, file);

	// write the rate of the sound
	fwrite(&samplerate, sizeof(unsigned int), 1, file);

	// write the bits of the sound
	fwrite(&bitrate, sizeof(unsigned int), 1, file);

	// write if the sound is mono or stereo
	fwrite(&stereo, sizeof(bool), 1, file);

	// write the size of the sound
	fwrite(&len, sizeof(unsigned long), 1, file);

	// write the data
	fwrite(&tag->data[tag->pos], tag->len - tag->pos, 1, file);
}