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

    /* Print complete file content following od hex format */
    /* od -A x -t x1z -v file.dat */

    close (fd);

    return 0;
}
