// screenify.c
// read in an Apple II disk file and a text file
// write them to a given block number
// probably clobber the directory if you're not careful
 
// Copyright 2023 Gordon JC Pearce <gordon@gjcp.net>
// 
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISKSIZE 143360

char buffer[DISKSIZE]; // size of Apple II disk
char line[80];	// max 64 chars per line, but leave space for overflow

void main(int argc, char *argv[]) {
	char *pos;
	int wptr;

	if (argc != 4) {
		printf("usage: screenify <source disk> <text file> <starting screen number>\n");
		exit(1);
	}


	FILE *disk = fopen(argv[1], "rb");
	FILE *text = fopen(argv[2], "r");

	if (!disk) {
		printf("could not open disk image %s\n", argv[1]);
		exit(1);
	}

	if (!text) {
		printf("could not open screens text %s\n", argv[2]);
		exit(1);
	}

	// read entire Apple II disk in, so we can overlay the text
	fread(&buffer, sizeof(unsigned char), DISKSIZE, disk);
	fclose(disk);
	
	// Apple II sectors are 256 bytes, so four sectors per 1kB screen
	// so all we need to do is step scr*1024 bytes into the disk buffer
	// and start writing
	// note that we make no attempt to do this "safely" and if it
	// scrambles the disk, so be it.

	// if the value passed isn't an int, it'll set wptr to zero
	// this will likely clobber the DOS sectors on the disk, so
	// maybe don't do that
	wptr = 1024 * atoi(argv[3]);

	// begin reading in the text file and copying it to the disk buffer
	while(!feof(text)) {
		bzero(line, 80);		// INTERPRET expects to find a zero at the end of the line
		fgets(line, 80, text);		// read in a maximum of 80 chars in a line
		pos = strchr(line, '\n');	// find the newline (hope there's a newline!)
		if (pos) {			// zero out the newline
			*pos = 0;
		}
		if ((pos - line) > 64) {	// warn if the line is longer than a Forth line
			printf("Oversize line: \n%s\n", line);
		}
		strncpy(buffer+wptr, line, 64);	// write it out to the disk buffer
		wptr += 64;			// next line in the output buffer
		if (wptr > DISKSIZE) {
			printf("text went off the end of the disk\n");
			exit(1);
		}

	}
	fclose(text);

	// write it back out
	disk = fopen(argv[1], "wb");
	fwrite(&buffer, sizeof(unsigned char), DISKSIZE, disk);
	fclose(disk);
}
