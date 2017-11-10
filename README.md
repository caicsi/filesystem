# filesystem
Final project for OS class


NOTE: I did not do this exactly, but you'll see
NOTE: Run make, then run the executable in build dir. To exit the shell properly, enter exit. Failing to run exit will result in a mem leak!


Make the shell:
Parent processor gives prompt
PP checks if user input is valid command
if so, fork child process to run command, wait for signal that child is done
child process accesses command and executes: there is a file for every command
child sends message to parent
if not, error message that it’s an invalid command.

how to organize:
the commands need to be accessible to child processes, so include them in the header.
maybe have an array of nodes? this would have info on each command that the parent can access to validate the command usage and call command:
char cmdName- just the name of the command, like “cd”. parent can loop through these to see if the command inputted exists
char funcName- name of the function that calls this specific command, like “cdExe” or something.
int minParam
int maxParam
