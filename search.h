/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   search.h
/
/  Program Purpose(s):
/    User-defined header file for search.c. 
/---------------------------------------------------------*/

#ifndef SEARCH_H
#define SEARCH_H

#define MAX_PATH_LEN 254

int get_path(char *path, char *envp[]);
int check_for_file(char *command, char *full_path, char *envp[]);
void test(char *envp[]);

#endif