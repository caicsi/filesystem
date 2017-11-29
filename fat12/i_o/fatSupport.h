#ifndef FAT_SUPPORT_H
#define FAT_SUPPORT_H

#include "bootSector.h"

int read_sector(int sector_number, char *buffer);
int write_sector(int sector_number, char *buffer);

void printBootSector(bootSector_t *boot);
int  readBootSector(bootSector_t *boot);

int  get_fat_entry(int fat_entry_number, char *fat);
void set_fat_entry(int fat_entry_number, int value, char *fat);

#endif
