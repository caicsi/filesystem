/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  13 December 2017
 * 
 * Description:   Implementation of the pwd command
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */
 
 
#include "../master.h"


/*
 * Pre: 	An optional vector of arguments, though no additional 
 * 			arguments are read for this command
 * Post: 	The current working directory is printed to stdout
 * Purpose: To print the current working directory
 */
int pwd(char **argv)
{
	// Does not read from FAT12 system correctly in current state
	
	int  bytes_read;
	char *buffer;
	
	if (fseek(FILE_SYSTEM_ID, 0, SEEK_CUR) == -1)
	{
		perror("fseek");
		return EXIT_FAILURE;
	}
	
	bytes_read = fread(buffer, sizeof(char), BYTES_PER_SECTOR, FILE_SYSTEM_ID);

	
	return EXIT_SUCCESS;
}
