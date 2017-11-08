/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Final Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  17 December 2017
 * 
 * Description:   Design and implement a file system
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */

#include <stdlib.h>
#include "cd.c"

#define NUM_CMDS = 11;
#define MAX_CMD_LENGTH = 6;
 
const char cmds[NUM_CMDS][MAX_CMD_LENGTH] = {"cat", "cd", "df", "ls",
	 "mkdir", "pbs", "pfe", "pwd", "rm", "rmdir", "touch"};
	 


