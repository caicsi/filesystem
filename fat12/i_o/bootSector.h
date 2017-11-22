#ifndef BOOT_SECTOR_H
#define BOOT_SECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bootSector
{
	int bytesPerSector,
		sectorsPerCluster,
		numOfFats,
		numReservedSectors,
		numRootEntries,
		totalSectorCount,
		sectorsPerFat,
		sectorsPerTrack,
		numOfHeads;
	
	char *bootSig; // in hex
	char *volId; // in hex
	char *volLabel;
	char *fileSysType;
} bootSector_t;

#endif
