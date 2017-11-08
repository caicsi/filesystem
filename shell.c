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
 
#include "commands/commands.h"


/*possible functions:
* validate(input) check if user input is a valid command, and call
*   correlating command program that will also check if it fulfills 
*   the requirements for that specific command to be called. 
* 	returns 
* execute(cmd) forks off child; child executes command, then returns signal.
* 
* main: loops through prompt and user input and child response. 
* 
*/

