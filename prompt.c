/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   prompt.c
/
/  Program Purpose(s):
/    Function to display a custom command prompt that 
/    includes the username, hostname, and a $.
/---------------------------------------------------------*/

#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include "prompt.h"
#include "stringlib.h"

/*---------- FUNCTION: show_prompt ------------------------- 
/  PURPOSE:
/    Displays a customized command prompt with the username,
/    hostname, and a static identifier for the shell ($).
/  
/  CALLER INPUT:
/    N/A-No input parameters. 
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/   N/A
/---------------------------------------------------------*/

void show_prompt() {
    struct passwd *passwd = getpwuid(getuid());
    char *username;
    if (passwd != NULL) {
        username = passwd->pw_name;
    } 
    else {
        username = "unknown";
    }

    char hostname[HOST_MAX] = {0};
    if (gethostname(hostname, HOST_MAX) == -1) {
        string_copy(hostname, "unknownhost\0");
    }

    write(2, ANSI_MAGENTA, string_len(ANSI_MAGENTA)); 
    write(2, username, string_len(username));
    write(2, "@", 1);
    write(2, hostname, string_len(hostname));
    write(2, ANSI_RESET, string_len(ANSI_RESET)); 
    write(2, ":", 1);
    write(2, ANSI_CYAN, string_len(ANSI_CYAN)); 
    write(2, "kash", 4);
    write(2, ANSI_RESET, string_len(ANSI_RESET)); 
    write(2, "$ ", 2);
}