/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  13 December 2017
 * 
 * Description:   Implementation of the pfe command
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */
 

#include "../fatSupport.h"


 /*
  * Pre:	 Two integer values
  * Post:	 Return success if the values are valid and failure if the 
  * 		 values are invalid
  * Purpose: To determine if the provided values are within an 
  * 		 appropriate range 
  * */
int checkRange(int x, int y)
{
	// The values used here are specific to sectors that correlate to 
	// FAT tables (primary or backup)
	if ((x < 2) || (x > y) || (y > 18) || ((x < 9) && (y > 9)))
	{
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


 /*
  * Pre:	 An optional list of arguments
  * Post:	 Entry values of logical sectors are printed to screen
  * Purpose: Print the 12-bit FAT entry values representing logical 
  * 		 sectors x to y
  * */
int pfe(char **argv)
{
	int  entOne = atoi(argv[1]), entTwo = atoi(argv[2]), i;

	if (checkRange(entOne, entTwo))
	{
		printf("Error: invalid range\n");
		return EXIT_FAILURE;
	}

	printEntries(entOne, entTwo);

	return EXIT_SUCCESS;
}


 /*
  * Pre:	 Two integer values indicating the range of sectors
  * Post:	 12-bit entry values are printed to screen
  * Purpose: Print the 12-bit FAT entry values representing logical 
  * 		 sectors x to y
  * */
int  printEntries(int entOne, int entTwo)
{
	char *buffer;

	buffer = readFAT12Table(1, buffer);

	// free(buffer);

	return EXIT_SUCCESS;
}


 /*
  * Pre:	 An integer value indicating a FAT table, and an adequate buffer
  * Post:	 The contents of the specified FAT table are read into the buffer
  * Purpose: To read a FAT table entirely into a buffer
  * */
char *readFAT12Table(int fatTable, char *buffer)
{
	int i, start = 0, end = 0;
	
	buffer = (char *) malloc(BYTES_PER_SECTOR * sizeof(char) * SIZE_OF_FAT);

	if (fatTable == 1)
	{
		start = 1;
		end = 9;
	}
	else if (fatTable == 2)
	{
		start = 10;
		end = 18;
	}

	for (i = start; i <= end; i++)
	{
		read_sector(i + 1, &buffer[i * BYTES_PER_SECTOR]);
	}

	return buffer;
}
