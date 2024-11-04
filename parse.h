/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   parse.h
/
/  Program Purpose(s):
/    User-defined header file for parse.c. 
/---------------------------------------------------------*/

#ifndef PARSE_H
#define PARSE_H

void parse_command(Command *command, char *tokens[], Job *job);
void parse_pipeline(Job *job, char *tokens[]);
void parse_job(Job *job);

#endif