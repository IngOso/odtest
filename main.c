/* main.c - main function file
 * Copyright (C) 2014 Adrian Alonso <aalonso00@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with self library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

#define   AMOUNT_OF_CHAR  16u    //Defines indicate amount of characters to process.

int
main(int argc, char **argv)
{
    int fd;
    char *file = NULL;
    unsigned char buff[16];

    unsigned int RowOffset = 0u;	//This variable indicate the offset to read the bytes
    unsigned int PrintIndex;		//This variable is use to indicate the position to print the string
    struct stat S_FILE_INFO;		//Structure to determine file size.
    size_t* Length;					//This variable contains size of the file
    unsigned long Counter = 0u;		//This variable is a counter for bytes printed

	    if(argc != 2)
	    {
		printf ("Usage: %s <file>\n", argv[0]);
		exit (1);
	    }

    file = argv[1];

    fd = open(file, O_RDONLY);

	    if(fd < 0)
	    {
		printf ("Error");
		exit(1);
	    }

    // The purpose of this program is emulate the behaviour of Od command for the format: "od -A x -t x1z -v file.dat".  
    fstat(fd,&S_FILE_INFO);				//Get file status.
    *Length = S_FILE_INFO.st_size;		//Get file length.
	
    while(RowOffset < *Length)			//print until counter will reach file size.
    {
	    pread(fd,buff,AMOUNT_OF_CHAR,RowOffset);	//Read 16 symbols and save into buffer.
	    printf("%06x ",RowOffset);					//Print start address.

	    
	    for(PrintIndex = 0; PrintIndex < AMOUNT_OF_CHAR; PrintIndex++)//Read and process one row.
	    {
			if(Counter >= *Length) //Counter value is greater than length?
			{//Yes-->
				printf("   ");				//Print empty.
				buff[PrintIndex] = ' ';		//Clear buffer position.
			}
			else
			{//No->
				
				printf("%02x ",buff[PrintIndex]);//Print the hex converted symbols.
				if(buff[PrintIndex] == 0x0A)// Is symbol next line??
				{//Yes->
					buff[PrintIndex] = '.';//Print "." instead on next line.
				}
				Counter++;//Increment counter.
			}
	    }
	    printf(">%s<\n",buff);//Print current row.
	    RowOffset = RowOffset + AMOUNT_OF_CHAR;//Increase the offset value to read the next line.
    } 

    close (fd);

    return 0;
}
