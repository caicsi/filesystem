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


int checkRange(int x, int y)
{
	if ((x <  2) || (x > y))
	{
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


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


int  printEntries(int entOne, int entTwo)
{
	char *buffer;

	buffer = readFAT12Table(1, buffer);

	free(buffer);

	return EXIT_SUCCESS;
}


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
