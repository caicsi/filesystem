/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  6 December 2017
 * 
 * Description:   Implementation of the commands
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

#ifndef NUM_CMDS
#define NUM_CMDS 5
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
	
	char *bootSig; // hex
	char *volId; // hex
	char *volLabel; // str
	char *fileSysType; // str
} bootSector_t;

// Useful shell functions
int exitShell(char **argv);
int help(char **argv);

// Other functions specific to the shell
int  executeCommand(char **argv);
int  launch(char **argv);
char **parseLine(char *line);
char *readLine();
void shellLoop();

// Function specific to cd command
int cd(char **argv);

// Functions specific to cat command
int  cat(char **argv);
bool isDir(const char *filename);
bool openFile(const char *filename);
bool readFile(int fd);

// Function specific to pwd command
int pwd(char **argv);

// Functions specific to pbs command
void printBootSector(bootSector_t *boot);
int  readBootSector(bootSector_t *boot);

#endif
