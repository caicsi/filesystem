#include "../fatSupport.h"


int checkRange(int x, int y)
{
	if ((x <  2) || (x > y)) // Note, may consider making 2 a constant
	{
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


int pfe(char **argv)
{
	int  sectOne = atoi(argv[1]), sectTwo = atoi(argv[2]), i;
	char *buffer;
	
	if (checkRange(sectOne, sectTwo))
	{
		printf("Error: invalid range\n");
		return EXIT_FAILURE;
	}

	for (i = sectOne; i <= sectTwo; i++)
	{
		// buffer = readFAT12Table(i, buffer);
		// printf("Entry %i: \n", i);
		// free(buffer);
	}

	return EXIT_SUCCESS;
}


char *readFAT12Table(int sectNum, char *buffer)
{
	buffer = (char *) malloc(BYTES_PER_SECTOR * sizeof(char));
	
	if (read_sector(sectNum, buffer) == -1)
	{
		printf("Something has gone wrong -- could not read the sector\n");
	}
	
	return buffer;
}
