#include "../fatSupport.h"


bool checkRange(int x, int y)
{
	if ((x <  2) || (x > y))
	{
		FALSE;
	}
	
	return TRUE;
}


int pfe(char **argv)
{
	int  sectOne = argv[1], sectTwo = argv[2], i;
	char *buffer;
	
	if (checkRange(sectOne, sectTwo) == FALSE)
	{
		printf("Error: invalid range\n");
		return EXIT_FAILURE;
	}	

	for (i = sectOne; i <= sectTwo; i++)
	{
		buffer = readFAT12Table(i, buffer);
		printf("Entry %i: %c", i, buffer[0]);
		free(buffer);
	}

	return EXIT_SUCCESS;
}


char *readFAT12Table(int sectNum, char *buffer)
{
	char *buffer;
	
	buffer = (char *) malloc(BYTES_PER_SECTOR * sizeof(char));
	
	if (read_sector(sectNum, buffer) == -1)
	{
		printf("Something has gone wrong -- could not read the sector\n");
	}
	
	return buffer;
}
