#ifndef BOOT_SECTOR_H
#define BOOT_SECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
	char *bootSig; // hex
	char *volId; // hex
	char *volLabel; // str
	char *fileSysType; // str
} bootSector_t;

#endif
