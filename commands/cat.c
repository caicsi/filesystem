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
 * Pre: 	None, other than optional arguments
 * Post: 	Contents of a file, or files, are printed to screen. Should something
 * 			cause an error, an appropriate error message will be noted
 * Purpose: To print the contents of one or more files to screen
 */
int cat(char **argv) // Note, this is main function of cat
{
	if (argv[1] == NULL) 
	{
		fprintf(stderr, "usage %s FILE [FILE] ...\n", argv[0]);
	}
	else
	{
		int i = 1;
		
		while (argv[i] != NULL)
		{
			if (isDir(argv[i])) // Check if argument is a directory
			{
				fprintf(stderr, "cat: %s: Is a directory\n", argv[i]);
			}
			else if (!openFile(argv[i])) // Printing contents of a file, if it exists
			{
				fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);	// Actually, this could be a existant directory
			}			
			
			i++;
		}
	}
	
	return 1;
}


/*
 * Pre: 	A specified filename
 * Post: 	True is returned if the filename is a directory, false otherwise
 * Purpose: To determine if an argument is a directory
 */
bool isDir(const char *filename)
{
	DIR *dir;
	
	// Attempt to open argument as a directory
	dir = opendir(filename);
	
	// If opened successfully, the argument is confirmed to be
	// a directory, which means it's an invalid argument
	if (dir != NULL)
	{
		closedir(dir);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


/*
 * Pre: 	A specified filename
 * Post: 	True is returned if the file is opened and read successfully, 
 * 		 	false otherwise
 * Purpose: To open a specific file and call the readFile function
 */
bool openFile(const char *filename)
{
	int fd;
	bool status = FALSE;
	
	// Attempt to open file for reading
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		return FALSE;
	}
	
	// If opened successfully, call read function
	status = readFile(fd);
	
	// Attempt to close file
	if (close(fd) != 0)
	{
		return FALSE;
	}
	
	return status;
}


/*
 * Pre: 	A file descriptor
 * Post: 	True is returned if the file is read, false otherwise
 * Purpose: To read the contents of a file to stdout
 */
bool readFile(int fd)
{
	char buffer[CAT_BUFSIZE];
	int  numRead, numWritten;
	
	// Read contents of the file into the buffer
	numRead = read(fd, buffer, CAT_BUFSIZE);
	
	// Write contents from buffer to stdout
	while (numRead > 0)
	{
		numWritten = write(STDOUT_FILENO, buffer, numRead);
		
		if (numWritten == -1)
		{
			return FALSE;
		}
		
		// Error if we fail to write all content to stdout
		if (numWritten != numRead)
		{
			fprintf(stderr, "Only wrote %i bytes out of %i\n", numWritten, numRead);
		}
		
		numRead = read(fd, buffer, CAT_BUFSIZE);
	}
	
	if (numRead == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
