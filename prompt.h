/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   prompt.h
/
/  Program Purpose(s):
/    User-defined header file for prompt.c. 
/---------------------------------------------------------*/

#ifndef PROMPT_H
#define PROMPT_H

#define ANSI_MAGENTA "\033[1;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RESET "\033[0m"
#define PATH_MAX 4096
#define HOST_MAX 253

void show_prompt();

#endif