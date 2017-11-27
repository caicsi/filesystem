/******************************************************************************
 * main: Sample for starting the FAT project.
 *
 * Authors:  Andy Kinley, Archana Chidanandan, David Mutchler and others.
 *           March, 2004.
 *****************************************************************************/

#include "bootSector.h"
#include <string.h>
#include "dda.h"
#include "fatSupport.h"

// 13 is NOT the correct number -- you fix it!
#define BYTES_TO_READ_IN_BOOT_SECTOR 13

/******************************************************************************
 * You must set these global variables:
 *    FILE_SYSTEM_ID -- the file id for the file system (here, the floppy disk
 *                      filesystem)
 *    BYTES_PER_SECTOR -- the number of bytes in each sector of the filesystem
 *
 * You may use these support functions (defined in FatSupport.c)CSI 385 
F
all 2017
Semester Project
Page 
3
Starting Byte
Length (in bytes)
Stored Data
0 
11 
Ignore 
11 
2 
Bytes per sector 
13 
1 
Sectors per cluster 
14 
2 
Number of reserved sectors 

 *    read_sector
 *    write_sector
 *    get_fat_entry
 *    set_fat_entry
 *****************************************************************************/

FILE* FILE_SYSTEM_ID;
int BYTES_PER_SECTOR = 512;

bootSector_t BOOT_SECTOR;

extern int read_sector(int sector_number, char* buffer);
extern int write_sector(int sector_number, char* buffer);

extern int  get_fat_entry(int fat_entry_number, char* fat);
extern void set_fat_entry(int fat_entry_number, int value, char* fat);

/******************************************************************************
 * main: an example of reading an item in the boot sector
 *****************************************************************************/

int main()
{
	// unsigned char* boot;            // example buffer

	// int mostSignificantBits;
	// int leastSignificantBits;
	// int bytesPerSector;

	// You must set two global variables for the disk access functions:
	//      FILE_SYSTEM_ID         BYTES_PER_SECTOR

	// Use this for the real floppy drive
	//  FILE_SYSTEM_ID = fopen(DISK_FDD0, "r+");


	// Use this for an image of a floppy drive
	FILE_SYSTEM_ID = fopen("floppy1", "r+");

	if (FILE_SYSTEM_ID == NULL)
	{
		printf("Could not open the floppy drive or image.\n");
		exit(1);
	}

	// Set it to this only to read the boot sector
	BYTES_PER_SECTOR = BYTES_TO_READ_IN_BOOT_SECTOR;

	// Then reset it per the value in the boot sector

	//boot = (unsigned char*) malloc(BYTES_PER_SECTOR * sizeof(unsigned char));

	readBootSector(BOOT_SECTOR);

	return 0;
}


// note: http://minirighi.sourceforge.net/html/fat12_8c-source.html
