#include "../fatSupport.h"

void printBootSector(bootSector_t *boot)
{
	printf("Bytes per sector           = %i\n", boot->bytesPerSector);
	printf("Sectors per cluster        = %i\n", boot->sectorsPerCluster);
	printf("Number of FATs             = %i\n", boot->numOfFats);
	printf("Number of reserved sectors = %i\n", boot->numReservedSectors);
	printf("Number of root entries     = %i\n", boot->numRootEntries);
	printf("Total sector count         = %i\n", boot->totalSectorCount);
	printf("Sectors per FAT            = %i\n", boot->sectorsPerFat);
	printf("Sectors per track          = %i\n", boot->sectorsPerTrack);
	printf("Number of heads            = %i\n", boot->numOfHeads);
	printf("Boot signature (in hex)    = 0x%x\n", boot->bootSig);
	printf("Volume ID (in hex)         = 0x");
	for (int i = 0; i < 4; i++) 
	{
		if (i == 3)
		{
			printf("%x\n", (unsigned int)(unsigned char)boot->volId[i]);
		}
		else {
			printf("%x", boot->volId[i]);
		}	
	}
	printf("Volume label               = %s\n", boot->volLabel);	
	printf("File system type           = %s\n", boot->fileSysType);	
	
	// Expected:
	// Boot signature (in hex) = 0x29
	// Volume ID (in hex)      = 0x244f429d
	// Volume label 		   = NO NAME
	// Filesystem type		   = FAT12 
	// concat from label       = NO NAME    FAT12   3ɎѼ�{�ٸ
}


int readBootSector()
{
	char 		 *buffer;
	int  		 mostSigBits, leastSigBits;
	bootSector_t *boot;

	buffer = (char *) malloc(BYTES_PER_SECTOR * sizeof(char));
	boot = (bootSector_t *) malloc(BYTES_PER_SECTOR * sizeof(bootSector_t));

	// read sector from file to buffer
	if (read_sector(0, buffer) == -1)
	{
		printf("Something has gone wrong -- could not read the boot sector\n");
	}

	// assign values to bootSector_t object
	
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

	// boot signature (hex)
	boot->bootSig = buffer[38];

	// volume ID (hex)
	//boot->volId = buffer[42];
	char volIdStr[4];
	for (int i = 42; i > 38; i--) 
	{
		volIdStr[42-i] = buffer[i];
	}
	boot->volId = volIdStr;

	// volume label
	//boot->volLabel = &buffer[43];
	unsigned char volLabelStr[11];
	for (int i = 0; i < 11; i++)
	{
		volLabelStr[i] = buffer[43+i];
	}
	boot->volLabel = volLabelStr;

	// filesys type	
	unsigned char fileSysStr[8];
	for (int i = 0; i < 8; i++)
	{
		fileSysStr[i] = buffer[54+i];
	}
	boot->fileSysType = fileSysStr;

	// free buffer after assigning values
	free(buffer);
	
	// print values of bootSector_t object
	printBootSector(boot);

	// free the bootSector_t object after printing values
	free(boot);

	return EXIT_SUCCESS;
}
