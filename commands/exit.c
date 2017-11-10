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
 * Post: 	The user is no longer running the shell
 * Purpose: To exit the shell properly and allow memory cleanup
 */
// Source: https://github.com/brenns10/lsh
int exitShell(char **argv)
{
	printf("Sad to see you go\n");
	
	return 0;
}
