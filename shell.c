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
 

#include "master.h"


// Source: https://github.com/brenns10/lsh


// Global array of custom commands
char *CMD_STRS[] = {"cd", "cat", "help", "exit", "pwd", "pbs"};
// Global parallel array of corresponding functions
int (*CMD_FUNCS[]) (char **) = {&cd, &cat, &help, &exitShell, &pwd, &readBootSector};
// NOTE: fat is a place holder at the moment for testing


 /*
  * Pre:	 An optional vector of arguments
  * Post:	 A specific command will be executed with the given arguments
  * Purpose: To execute a command from the user
  * */
int executeCommand(char **argv)
{
	pid_t pid, wpid;
	int   status, i;
	bool  found = FALSE;

	if (argv[0] == NULL)
	{
		// With no command entered, we return 1 
		// just to continue the shell loop
		return EXIT_FAILURE;
	}

	pid = fork();

	if (pid == 0) // Child created successfully
	{
		// With a command entered, we run through the array of strings
		// until we find which command was entered. After doing so, we
		// run the corresponding function in the parallel array of functions
		for (i = 0; i < NUM_CMDS; i++) 
		{
			if (strcmp(argv[0], CMD_STRS[i]) == 0) 
			{
				(*CMD_FUNCS[i])(argv);
				found = TRUE;
			}
		}
		
		if (found == FALSE)
		{
			printf("Command is unrecognized.\n");
		}
		
		exit(EXIT_FAILURE);
	} 
	else if (pid < 0) // Child failed
	{
		perror("fork");
	}
	else // Working in parent process
	{
		// This loop is to allow the parent to wait for
		// the child to terminate
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	// We intentional return failure to continue running the shell 
	// loop. 'exit' will result in success and cause the loop to 
	// terminate
	if (strcmp(argv[0], "exit") == 0)
	{
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}


/*
  * Pre:	 An optional vector of arguments
  * Post:	 A user will have interacted with a custom shell
  * Purpose: To run a custom shell with built-in commands
  * */
int main(int argc, char **argv)
{
	printf("Attempting to open floppy...\n");
		
	FILE_SYSTEM_ID = fopen(FLOPPY_NAME, "r+");

	if (FILE_SYSTEM_ID == NULL)
	{
		printf("Could not open the floppy drive or image.\n");
		exit(1);
	}
	
	sleep(1);
	
	printf("Floppy is open...\n\nStarting shell. Enter 'exit' to leave.\n\n");
	
	sleep(1);
	
	// Run the loop that generates the shell
	shellLoop();

	printf("\nClosing floppy...\n");

	fclose(FILE_SYSTEM_ID);
	
	sleep(1);
	
	printf("Floppy is closed...\n\nExiting shell...Sad to see you go\n");
	
	sleep(1);

	return EXIT_SUCCESS;
}


 /*
  * Pre:	 A line of input as provided by the user
  * Post:	 The provided line is parsed and split into tokens
  * Purpose: To create an array of tokens that will serve as the
  * 		 vector of arguments when executing a command
  * */
char **parseLine(char *line)
{
	int  bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) 
	{	  
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// First pass of line to strtok
	token = strtok(line, TOK_DELIM);
	
	// After the initial pass, we parse through token until
	// we have appropriately differentiated each token into
	// the tokens array
	while (token != NULL) 
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize) 
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) 
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}
	
	tokens[position] = NULL;
	
	return tokens;
}


 /*
  * Pre:	 None
  * Post:	 Information entered to a prompt by the user will be read
  * 		 and returned
  * Purpose: To read input from the user of the custom shell
  * */
char *readLine()
{
	char    *line = NULL;
	ssize_t bufsize = 0; // Function getline() will allocate a buffer
	
	// Read from stdin and store input in line
	getline(&line, &bufsize, stdin);

	return line;
}


 /*
  * Pre:	 None
  * Post:	 A loop will have executed, generating a custom shell
  * Purpose: To run a custom shell with built-in commands
  * */
void shellLoop()
{
	char *line; // Complete line entered in the prompt
	char **argv; // Vector of arguments within a supplied line
	int  status;

	do {
		printf("goodShell> $ ");
		line = readLine();
		argv = parseLine(line);
		status = executeCommand(argv);

		free(line);
		free(argv);
	} while (status);
}
