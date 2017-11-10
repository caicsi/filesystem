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

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "cat.c"

// Total number of commands implemented
#ifndef NUM_CMDS
#define NUM_CMDS 11
#endif

// Max length for name of a command (including '\0')
#ifndef
#define MAX_CMD_LENGTH 6
#endif

// Size of buffer for i/o purposes
#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 4096
#endif

typedef enum {FALSE, TRUE} bool;

// Char array that stores names of implemented commands
const char cmds[NUM_CMDS][MAX_CMD_LENGTH] = {"cat", "cd", "df", 
											 "ls", "mkdir", "pbs", 
											 "pfe", "pwd", "rm", 
											 "rmdir", "touch"};

// Functions specific to cat command
bool cat(const char *filename);
bool isDir(const char *filename);
bool readFile(int fd);

#endif
