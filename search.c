/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   search.c
/
/  Program Purpose(s):
/    Custom library built to manage a linear search for file
/    names using the PATH environment variable. 
/---------------------------------------------------------*/

#include <sys/stat.h>
#include <unistd.h>
#include "stringlib.h"
#include "search.h"

#include <stdio.h>



/*---------- FUNCTION: get_path ----------------------------
/  PURPOSE:
/    Retrieves the PATH environment variable from the provided
/    environment variables and copies its value to the specified 
/    path buffer.
/  
/  CALLER INPUT:
/    char *path
/      A pointer to a buffer where the PATH value will be stored. 
/  
/    char *envp[]
/      An array of strings representing the environment variables.
/  
/  CALLER OUTPUT:
/    Returns 0 on success, indicating that the PATH variable was found.
/    Returns 1 if the PATH variable is not found.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/---------------------------------------------------------*/
int get_path(char *path, char *envp[]) {
    int i = 0;

    for (i = 0; envp[i] != NULL; i++) {
        if (str_comp_by_len(envp[i], "PATH=", 5) == 0) {
            string_copy((envp[i] + 5), path);
            return 0;
        }
    }

    return 1; /* not found */
}


/*---------- FUNCTION: check_for_file ----------------------
/  PURPOSE:
/    Checks if the specified command exists in the directories 
/    listed in the PATH. If found, it adds the full path to 
/    the command.
/  
/  CALLER INPUT:
/    char *command
/      A pointer to the command.
/  
/    char *full_path
/      A pointer to a buffer where the full path of the command 
/      will be stored.
/  
/    char *envp[]
/      An array of strings representing the environment variables.
/  
/  CALLER OUTPUT:
/    Returns 0 if the command is found and the full path is 
/    constructed successfully.
/    Returns 1 if the command is not found.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/     N/A
/---------------------------------------------------------*/
int check_for_file(char *command, char *full_path, char *envp[]) {
    struct stat sb;
    int path_index = 0;
    char path[MAX_PATH_LEN];
    int i = 0;
    int j = 0;

    if (get_path(path, envp) != 0) {
        string_copy("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games", path);
    } /* assigns path and sets default if "PATH" not in envp */

    while (path[i] != '\0') {

        path_index = 0;
        j = 0;

        while(path[i] != ':' && path[i] != '\0') {
            full_path[path_index++] = path[i++];
        } /* append path to full_path */

        full_path[path_index++] = '/'; /* appending before command */

        while (command[j] != '\0') {
            full_path[path_index++] = command[j++];
        } /* appending the command to full_path */
        
        full_path[path_index] = '\0';

        if (stat(full_path, &sb) == 0) {
            return 0; /* file found */
        }

        if (path[i] == ':') {
            i += 1; /* skip over the ':' delimiter before restarting loop */
        }

    } /* null terminator reached */

    return 1; /* file not found */
}



