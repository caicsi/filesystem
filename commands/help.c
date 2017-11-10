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
 * Post: 	A couple of messages are printed to screen
 * Purpose: To give credit to the project that much of the 
 * 			shell is derived from
 */
// Source: https://github.com/brenns10/lsh
int help(char **argv)
{
	printf("Credit to Stephen Brennan's GitHub Project\n\n");
	printf("Type program names and arguments, and hit enter\n");
	
	return 1;
}
