/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   errorcodes.h
/
/  Program Purpose(s):
/    User-defined header file to contain various error messages
/    which will be used in multiple other files.
/---------------------------------------------------------*/

#ifndef ERRORCODES_H
#define ERRORCODES_H

#define ERROR_MEMORY "Error: memory allocation failure.\n\r"
#define ERROR_READ "Error: failed to read input.\n\r"
#define ERROR_INVALID_COMMAND "Error: PEBKAC--invalid command.\n\r"
#define ERROR_PIPE_FAILED "Error: pipe creation failed.\n\r"
#define ERROR_CLOSE_FAILED "Error: Failed to close pipe.\n\r"
#define ERROR_FORK_FAILED "Error: fork creation failed.\n\r"
#define ERROR_EXECVE "Error: program failed to execute.\n\r"
#define ERROR_START_BACKGROUND "Error: process started in background.\n\r"
#define ERROR_OPEN_FILE "Error: file was not opened.\n\r"
#define ERROR_NO_COMMAND "Error: no command was entered.\n\r"
#define ERROR_WAIT_FAILED "Error: Wait failed.\n\r"
#define ERROR_DUP2_FAILED "Error: dup2 failed.\n\r"
#define ERROR_SIGNAL_FAILED "Error: Failed to set signal handler.\n\r"

#endif