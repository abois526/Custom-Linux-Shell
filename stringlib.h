/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.h
/
/  Program Purpose(s):
/    User-defined header file for stringlib.c. 
/---------------------------------------------------------*/
#include <sys/types.h>
#ifndef STRINGLIB_H
#define STRINGLIB_H

int string_comp(const char *str1, const char *str2);
int string_len(const char *str);
void string_copy(const char *src, char *dst);
void pid_to_string(pid_t pid, char *buffer);
int str_comp_by_len(const char *str1, const char *str2, int len);


#endif