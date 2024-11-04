/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   jobs.h
/
/  Program Purpose(s):
/    User-defined header file for jobs.c. 
/---------------------------------------------------------*/

#ifndef JOBS_H
#define JOBS_H

#include <stddef.h>
#include "commands.h"

#define MAX_PIPELINE_LENGTH 10

/*---------- STRUCTURE: Job --------------------------------
/  INFO:
/    Data structure for representing a job.
/  
/  ATTRIBUTES:
/    Command pipeline[]
/      An array of Command structs, each representing an individual
/      linux command, to help facilitate piping commands together.
/    unsigned int num_stages
/      The number of pipeline stages i.e. the number of commands
/      currently in the pipeline. 
/    char *outfile_path
/      The filepath to be used for output redirection. If the job 
/      requires no output redirection, this value will be NULL.
/    char *infile_path
/      The filepath to be used for input redirection. If the job 
/      requires no output redirection, this value will be NULL.
/    int background
/      Represents if the job will run as a foreground or background
/      process (0 = foreground, !0 = background).
/---------------------------------------------------------*/
typedef struct {
    Command pipeline[MAX_PIPELINE_LENGTH];
    unsigned int num_stages;
    char *outfile_path;
    char *infile_path;
    int background;
} Job;

void init_job(Job *job);
void run_job(Job *job);
pid_t process_job(Job *job, int stage, int *pipefd);

#endif