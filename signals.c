/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   signals.c
/
/  Program Purpose(s):
/    Functions to handle signals for child processes
/    and interrupts.
/---------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "signals.h"
#include "globals.h"
#include "prompt.h"
#include "stringlib.h"

/*Globals for child reaping and background handling*/
volatile sig_atomic_t child_exit = 0;
int num_bg_jobs = 0;
BackgroundJob bg_jobs[MAX_BG_JOBS];

/*---------- FUNCTION: child_signal ------------------------
/  PURPOSE:
/    Handles SIGCHLD signal. Sets a flag to indicate
/    that a child processes has exited, and needs cleanup.
/  
/  CALLER INPUT:
/    int sig
/      The signal number.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Only sets a flag. Does not immediately reap child 
/      processes do to reaping processes to fast for parent.
/---------------------------------------------------------*/
void child_signal(int sig){

    child_exit = 1;

}
/*---------- FUNCTION: reap_children -----------------------
/  PURPOSE:
/    Reaps child processes that have exited, preventing 
/    zombie processes.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/   N/A
/---------------------------------------------------------*/
void reap_children(){

    pid_t pid;
    int status, i;
    char pid_str[32];

    if (child_exit) {
        
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {

            for (i = 0; i < num_bg_jobs; i++) {

                if (bg_jobs[i].pid == pid) {

                    write(STDOUT, "[", 1);
                    write(STDOUT, bg_jobs[i].pid_str, string_len(bg_jobs[i].pid_str));
                    write(STDOUT, "] done.\n", 8);

                    for (int j = i; j < num_bg_jobs - 1; j++) {
                        bg_jobs[j] = bg_jobs[j + 1]; 
                    }

                    num_bg_jobs--;
                    break; 
                }
            }
        }
        child_exit = 0;
    }
}

/*---------- FUNCTION: interrupt_block --------------------- 
/  PURPOSE:
/    Handles the SIGINT signal. Preventing Ctrl-C from
/    terminating the shell during user input.
/  
/  CALLER INPUT:
/    int sig
/      The signal number received.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/   N/A
/---------------------------------------------------------*/
void interrupt_block(int sig){

    /*do nothing*/

}