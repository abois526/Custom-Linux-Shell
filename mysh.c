/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   kash.c
/
/  Program Purpose(s):
/    Implements a simple command-line shell that processes 
/    user input, manages job execution, and handles signals 
/    for background processes.
/---------------------------------------------------------*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "commands.h"
#include "jobs.h"
#include "memory.h"
#include "prompt.h"
#include "stringlib.h"
#include "parse.h"
#include "signals.h"
#include "errorcodes.h"
#include "globals.h"

/*---------- FUNCTION: main --------------------------------
/  PURPOSE:
/    Implements the main loop, which processes input commands
/    until the user exits the program.
/  
/  CALLER INPUT:
/    N/A-No input parameters.
/  
/  CALLER OUTPUT:
/    Returns '0' upon successful exit.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/   N/A
/---------------------------------------------------------*/
int main() {

    Job job;

    signal(SIGINT, interrupt_block);
    signal(SIGCHLD, child_signal);

    while (1) {

        reap_children();
        show_prompt();
        init_job(&job);
        parse_job(&job);
        
        if (job.pipeline[0].argv[0] == NULL) {
            write(STDOUT, "", 1);
            init_job(&job);
            continue;
        }

        if (string_comp(job.pipeline[0].argv[0], "exit") == 0) {
            break;
        }

        run_job(&job);
        
    }

    return 0;
    
}