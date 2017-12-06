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
 * Pre: 	An optional vector of arguments, though no additional 
 * 			arguments are read for this command
 * Post: 	The current working directory is printed to stdout
 * Purpose: To print the current working directory
 */
int pwd(char **argv)
{
	int c, i;
	
	char cwd[PWD_BUFSIZE];
   
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		fprintf(stdout, "CWD: %s\n", cwd);
	}
	
	if (fseek(FILE_SYSTEM_ID, 0, SEEK_CUR) == 0)
	{
		fprintf(stdout, "CWD: %s\n", cwd);
		
	}
	else
	{
		perror("getcwd");
	}
	
	return EXIT_SUCCESS;
}
