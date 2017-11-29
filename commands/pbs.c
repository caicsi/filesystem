#include "../fatSupport.h"


void printBootSector(bootSector_t *boot)
{
	printf("Bytes per sector           = %i (512 expected)\n", boot->bytesPerSector);
	printf("Sectors per cluster        = %i (1 expected)\n", boot->sectorsPerCluster);
	printf("Number of FATs             = %i (2 expected)\n", boot->numOfFats);
	printf("Number of reserved sectors = %i (1 expected)\n", boot->numReservedSectors);
	printf("Number of root entries     = %i (224 expected)\n", boot->numRootEntries);
	printf("Total sector count         = %i (2880 expected)\n", boot->totalSectorCount);
	printf("Sectors per FAT            = %i (9 expected)\n", boot->sectorsPerFat);
	printf("Sectors per track          = %i (18 expected)\n", boot->sectorsPerTrack);
	printf("Number of heads            = %i (2 expected)\n", boot->numOfHeads);
}


int readBootSector(bootSector_t *boot)
{
	char *buffer;
	int  mostSigBits, leastSigBits;

	buffer = (char*) malloc(BYTES_PER_SECTOR * sizeof(char));

	if (read_sector(0, buffer) == -1)
	{
		printf("Something has gone wrong -- could not read the boot sector\n");
	}
	
	// assign values
	
	// bytes per sector
	mostSigBits = (((int) buffer[12]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[11]) & 0x000000ff;
	boot->bytesPerSector = mostSigBits | leastSigBits;
	
	// sects per cluster
	mostSigBits = ((int) buffer[13]) & 0x000000ff;
	boot->sectorsPerCluster = mostSigBits;
	
	// num of fats
	mostSigBits = ((int) buffer[16]) & 0x000000ff;
	boot->numOfFats = mostSigBits;
	
	// num reserved sectors
	mostSigBits = (((int) buffer[15]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[14]) & 0x000000ff;
	boot->numReservedSectors = mostSigBits | leastSigBits;
	
	// num root entries
	mostSigBits = (((int) buffer[18]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[17]) & 0x000000ff;
	boot->numRootEntries = mostSigBits | leastSigBits;

	// total sect count
	mostSigBits = (((int) buffer[20]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[19]) & 0x000000ff;
	boot->totalSectorCount = mostSigBits | leastSigBits;

	// sects per fat
	mostSigBits = (((int) buffer[23]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[22]) & 0x000000ff;
	boot->sectorsPerFat = mostSigBits | leastSigBits;

	// sects per track
	mostSigBits = (((int) buffer[25]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[24]) & 0x000000ff;
	boot->sectorsPerTrack = mostSigBits | leastSigBits;

	// num of heads
	mostSigBits = (((int) buffer[27]) << 8) & 0x0000ff00;
	leastSigBits = ((int) buffer[26]) & 0x000000ff;
	boot->numOfHeads = mostSigBits | leastSigBits;

	free(buffer);

	return EXIT_SUCCESS;
}
