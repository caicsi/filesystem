/*
 * Author: 		  Cai Blanchard, Max Capote
 * Class: 		  CSI-385-201
 * Assignment: 	  Semester Project
 * Date Assigned: 25 October 2017
 * Due Date: 	  13 December 2017
 * 
 * Description:   Implementation of a help command
 * 
 * Certification of Authenticity:
 * We certify that this assignment is entirely our own work 
 * and all additional sources are cited. 
 */
 
 
#include "../master.h"


/*
 * Pre: 	An optional vector of arguments
 * Post: 	A few messages are printed to screen
 * Purpose: To give credit to the project that much of the 
 * 			shell is derived from and inform the user of 
 * 			valid commands
 */
int help(char **argv)
{
	printf("Credit to Stephen Brennan's GitHub Project\n\n");
	printf("Type a command name, provide arguments if applicable, and hit enter.\n");
	printf("Commands implemented:\nhelp\npbs\nexit\n");

	return EXIT_SUCCESS;
}
