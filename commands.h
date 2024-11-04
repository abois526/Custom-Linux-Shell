/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   commands.h
/
/  Program Purpose(s):
/    User-defined header file for commands.c. 
/---------------------------------------------------------*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_ARGS 256 
#define BUFFER_SIZE 1024

/*---------- STRUCTURE: command ----------------------------
/  INFO:
/    Data structure for representing a linux command. 
/  
/  ATTRIBUTES:
/    char *argv[]
/      an array of pointers to dynamically allocated strings
/      representing entered arguments 
/    unsigned int argc
/      argument count (the size of the array)
/---------------------------------------------------------*/
typedef struct {
    char *argv[MAX_ARGS+1];
    unsigned int argc;
} Command;

void get_command(char *tokens[]);
void run_command(Command *command);
void tokenize(char *tokens[], char buffer[]);

#endif