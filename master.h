/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  13 December 2017
 * 
 * Description:  Primary header file for the c programs
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */

#ifndef MASTER_H
#define MASTER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include "dda.h"

#ifndef NUM_CMDS
#define NUM_CMDS 6
#endif

#ifndef TOK_BUFSIZE
#define TOK_BUFSIZE 64
#endif

#ifndef TOK_DELIM
#define TOK_DELIM " \t\r\n\a"
#endif

#ifndef CAT_BUFSIZE 
#define CAT_BUFSIZE 4096
#endif

#ifndef PWD_BUFSIZE
#define PWD_BUFSIZE 1024
#endif

#ifndef BYTES_PER_SECTOR
#define BYTES_PER_SECTOR 512
#endif

#ifndef FLOPPY_NAME
#define FLOPPY_NAME "floppy1"
#endif

#ifndef VOL_ID
#define VOL_ID 4
#endif

#ifndef VOL_LABEL
#define VOL_LABEL 11
#endif

#ifndef FILE_SYS_TYPE
#define FILE_SYS_TYPE 8
#endif

#ifndef SIZE_OF_FAT
#define SIZE_OF_FAT 9
#endif

FILE *FILE_SYSTEM_ID;

typedef enum {FALSE, TRUE} bool;

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
	
	char bootSig; // hex
	char *volId; // hex
	char volLabel[VOL_LABEL]; // str
	char *fileSysType; // str
} bootSector_t;

// Primary functions for the shell
int  executeCommand(char **argv);
char **parseLine(char *line);
char *readLine();
void shellLoop();

// A help function for the shell
int help(char **argv);

// Functions specific to pbs command
int  pbs();
void printBootSector(bootSector_t *boot);
void readBootSector(bootSector_t *boot);

// ------------------------------------------
// Function specific to cd command
int cd(char **argv);

// Functions specific to cat command
int  cat(char **argv);
bool isDir(const char *filename);
bool openFile(const char *filename);
bool readFile(int fd);

// Function specific to pwd command
int pwd(char **argv);
// ------------------------------------------

// Functions specific to pfe command
int  checkRange(int x, int y);
int  pfe(char **argv);
int  printEntries(int entOne, int entTwo);
char *readFAT12Table(int fatTable, char *buffer);

#endif
