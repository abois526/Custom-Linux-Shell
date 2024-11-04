/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   commands.c 
/
/  Program Purpose(s):
/    Fucntions for command processing, like reading user input,
/    tokenizing input, and executing commands.
/---------------------------------------------------------*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "errorcodes.h"
#include "commands.h"
#include "memory.h"
#include "prompt.h"
#include "signals.h"
#include "globals.h"
#include "stringlib.h"

/*---------- FUNCTION: get_command -------------------------
/  PURPOSE:
/    Reads a command from standard input, processes it, and 
/    stores the tokenized input into an array.
/  
/  CALLER INPUT:
/    char *tokens[]
/      - Stores an array of tokens generated from the input.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the input will be less than BUFFER_SIZE.
/
/---------------------------------------------------------*/

void get_command(char *tokens[]) {

    ssize_t bytes_read;
    char *p_buffer;
    

    p_buffer = alloc(BUFFER_SIZE);
    if (p_buffer == NULL) {
        write(STDERR, ERROR_MEMORY, string_len(ERROR_MEMORY));
        return;
    }

    bytes_read = read(STDIN, p_buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        p_buffer[bytes_read] = '\0'; /* same as *(p_buffer + bytes_read) */

        if (p_buffer[0] == '\n' || p_buffer[0] == '\0') {
            free_all();
            return;
        }

    }
    else {
        write(STDERR, ERROR_READ, string_len(ERROR_READ));
        return;
    }
    
    tokenize(tokens, p_buffer);

    free_all();

}

/*---------- FUNCTION: run_command -------------------------
/  PURPOSE:
/    Executes a command by forking a new process and using execve()
/    to run the command.
/  
/  CALLER INPUT:
/    Command *command
/      - A pointer to a Command structure containing the command's arguments.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Deprecated: No longer used and has been replaced by function 
/      that supports pipelines and I/O redirection.
/    - Assumes that command->argv is populated and terminated with NULL.
/---------------------------------------------------------*/

void run_command(Command *command) {

    pid_t pid;
    int status;
    char * const newenvp[] = {NULL};
    pid = fork();

    if (pid == 0) {
        if (execve(command->argv[0] , command->argv , newenvp) == -1) {
            write(STDERR, ERROR_INVALID_COMMAND, string_len(ERROR_INVALID_COMMAND));
            _exit(1); /* make sure child exits if error */
        }
    }
    else {

        if(waitpid(pid, &status, 0) == -1){

            write(STDERR, ERROR_WAIT_FAILED, string_len(ERROR_WAIT_FAILED));
            exit(1); 

        }
    }

}


/*---------- FUNCTION: tokenize ----------------------------
/  PURPOSE:
/    Breaks a buffer of user input into separate command line arguments, 
/    using whitespace as the delimiter.
/  
/  CALLER INPUT:
/    char *tokens[]
/      - Stores an array of tokens generated from the input.
/    char buffer[]
/      - The buffer containing the user input.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the tokens array has enough space to store all tokens from 
/      the buffer.
/    - Assumes that the buffer contains valid input and is null-terminated.
/---------------------------------------------------------*/

void tokenize(char *tokens[], char buffer[]) {

    int i = 0;
    int token_index = 0; 
    char *start = 0; 

    while (buffer[i] != '\0') { 

        if (buffer[i] != ' ' && buffer[i] != '\n') { 

            if (start == 0) { 

                start = &buffer[i];
            }
        }
        else { 

            if (start != 0) {

                buffer[i] = '\0';
                tokens[token_index++] = start; 
                start = 0;
            }
        }

        i++;

    }

    if (start != 0) {

        tokens[token_index++] = start; 

    }

    tokens[token_index] = 0;

}
