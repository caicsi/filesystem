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
 
 
#include "../master.h"


/*
 * Pre: 	An optional vector of arguments
 * Post: 	The user's working directory is changed
 * Purpose: Change to a desired directory
 */
// Source: https://github.com/brenns10/lsh
int cd(char **argv)
{
	if (argv[1] == NULL) 
	{
		char *home = getenv("HOME");
		
		if (home == NULL)
		{
			perror("getenv");
		}
		
		if (chdir(home) != 0)
		{
			perror("chdir");
		}
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("chdir");
		}
	}
	
	return EXIT_SUCCESS;
}
