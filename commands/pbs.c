/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  13 December 2017
 * 
 * Description:   Implementation of the pbs command
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */
 

#include "../fatSupport.h"


/*
 * Pre:		A FAT12 image must be available for reading
 * Post:	Information about the bootSector_t object is printed
 * 			to screen
 * Purpose: To display the information in the boot sector of the 
 * 			FAT12 image
 * */
int pbs()
{
	bootSector_t *boot;
	
	boot = (bootSector_t *) malloc(BYTES_PER_SECTOR * sizeof(bootSector_t));
	
	// Assign values to bootSector_t object	from the boot sector
	readBootSector(boot);

	// free the bootSector_t object after printing values
	free(boot);
	
	return EXIT_SUCCESS;
}


/*
 * Pre:		A bootSector_t object must be passed
 * Post:	Information about the bootSector_t object is printed
 * 			to screen
 * Purpose: To display the information in the boot sector of the 
 * 			FAT12 image
 * */
void printBootSector(bootSector_t *boot)
{
	int i;
	
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
	
	for (i = 0; i < VOL_ID; i++) 
	{
		if (i == (VOL_ID - 1))
		{
			printf("%x\n", (unsigned int)(unsigned char)boot->volId[i]);
		}
		else
		{
			printf("%x", boot->volId[i]);
		}
	}
	
	printf("Volume label               = ");
	
	for (i = 0; i < VOL_LABEL; i++) 
	{
		printf("%c", boot->volLabel[i]);
	}
	
	printf("\nFile system type           = %s\n", boot->fileSysType);
}


/*
 * Pre:		A bootSector_t object must be passed
 * Post:	Information in the boot sector of the FAT12 image
 * 			is assigned to a bootSector_t object
 * Purpose: To read from the FAT12 boot sector and then assign 
 * 			values to an object
 * */
void readBootSector(bootSector_t *boot)
{
	char *buffer;
	int  mostSigBits, leastSigBits, i;

	buffer = (char *) malloc(BYTES_PER_SECTOR * sizeof(char));

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
	char volIdStr[VOL_ID];
	
	for (i = 42; i > 38; i--) 
	{
		volIdStr[42 - i] = buffer[i];
	}
	
	boot->volId = volIdStr;

	// volume label
	char volLabelStr[VOL_LABEL];
	
	for (i = 0; i < VOL_LABEL; i++)
	{
		volLabelStr[i] = buffer[43 + i];
	}
	
	for (i = 0; i < VOL_LABEL; i++)
	{
		boot->volLabel[i] = volLabelStr[i];
	}

	// filesys type	
	char fileSysStr[FILE_SYS_TYPE];
	
	for (i = 0; i < FILE_SYS_TYPE; i++)
	{
		fileSysStr[i] = buffer[54 + i];
	}

	boot->fileSysType = fileSysStr;

	// free buffer after assigning values
	free(buffer);
	
	// print values of bootSector_t object
	printBootSector(boot);
}
