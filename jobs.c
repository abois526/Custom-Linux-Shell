/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   jobs.c
/
/  Program Purpose(s):
/    Functions to manage job execution including 
/    initializing jobs, running them in the foreground or 
/    background, and handling I/O redirection.
/---------------------------------------------------------*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "jobs.h"
#include "globals.h"
#include "errorcodes.h"
#include "stringlib.h"
#include "signals.h"

#define READ_END  0
#define WRITE_END 1


/*---------- FUNCTION: init_job ----------------------------
/  PURPOSE:
/    Initializes the Job struct by setting default values.
/  
/  CALLER INPUT:
/    Job *job
/      - A pointer to a Job struct.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that job is a valid pointer to a Job structure.
/---------------------------------------------------------*/
void init_job(Job *job) {
    job->num_stages = 0;
    job->outfile_path = NULL;
    job->infile_path = NULL;
    job->background = 0;
}


/*---------- FUNCTION: run_job -----------------------------
/  PURPOSE:
/    Executes a Job with multiple stages. Creates pipes for ipc 
/    and forks child processes to run each command as needed.
/  
/  CALLER INPUT:
/    Job *job
/      - A pointer to a Job struct.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the job structure has been properly configured.
/---------------------------------------------------------*/
void run_job(Job *job){

    int stage;
    int status;
    pid_t pids[job->num_stages];
    int pipefd[2 * (job->num_stages - 1)];

    /*Create pipes based on number of stages*/
    for (stage = 0; stage < job->num_stages - 1; stage++){
        if (pipe(pipefd + stage * 2) == -1) {

            write(STDERR, ERROR_PIPE_FAILED, string_len(ERROR_PIPE_FAILED));
            exit(1);

        }
    }

    /*Calls process_job to fork each stages child*/
    for(stage = 0; stage < job->num_stages; stage++){

        pids[stage] = process_job(job, stage, pipefd);

    }

    /*Close parents unused pipe ends*/
    for (stage = 0; stage < job->num_stages - 1; stage++) {

        /*Close read end*/
        if (close(pipefd[stage * 2]) == -1) {

            write(STDERR, ERROR_CLOSE_FAILED, string_len(ERROR_CLOSE_FAILED));
            exit(1);

        }
        /*Close write end*/
        if (close(pipefd[stage * 2 + 1]) == -1) {

            write(STDERR, ERROR_CLOSE_FAILED, string_len(ERROR_CLOSE_FAILED));
            exit(1);

        }
    }

    /*Wait for child to complete if foreground*/
    if(job->background == 0){

        for(stage = 0; stage < job->num_stages; stage++){

            if(waitpid(pids[stage], &status, 0) == -1){

                write(STDERR, ERROR_WAIT_FAILED, string_len(ERROR_WAIT_FAILED));
                exit(1);

            }
        }
    }else{ /*Notify user of background job*/

        if (num_bg_jobs < MAX_BG_JOBS) {
            bg_jobs[num_bg_jobs].pid = pids[0];
            pid_to_string(bg_jobs[num_bg_jobs].pid, bg_jobs[num_bg_jobs].pid_str);
            bg_jobs[num_bg_jobs].job_num = num_bg_jobs + 1;
            num_bg_jobs++;

            write(STDOUT, "Background job [", 17);
            write(STDOUT, bg_jobs[num_bg_jobs - 1].pid_str, string_len(bg_jobs[num_bg_jobs - 1].pid_str));
            write(STDOUT, "] started.\n", 11);
        }
        else{
            write(STDERR, "Maximum background jobs reached.\n", 34);
        }
    }
    
}

/*---------- FUNCTION: process_job -------------------------
/  PURPOSE:
/    Forks a new process to execute a stage of the job and 
/    sets up input and output redirection as needed.
/  
/  CALLER INPUT:
/    Job *job
/      - A pointer to a Job struct.
/    int stage
/      - The index of the current stage within the job.
/    int *pipefd
/      - An array of file descriptors for the pipes connecting 
/        the stages.
/  
/  CALLER OUTPUT:
/    Returns the PID of the created child process.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the stage index is within bounds of 
/      the job's number of stages.
/    - Assumes that the commands have been properly populated 
/      in the job struct.
/---------------------------------------------------------*/
pid_t process_job(Job *job, int stage, int *pipefd){


    pid_t pid;

    int input_fd = -1;
    int output_fd = -1;
    int i;

    /*Fork a new process*/
    pid = fork();

    if (pid == -1) {

        write(STDERR, ERROR_FORK_FAILED, string_len(ERROR_FORK_FAILED));
        exit(1);

    }
    
    /*Child starts here*/
    if(pid == 0){ 

        /*Allow child to be interrupted*/
        if (signal(SIGINT, SIG_DFL) == SIG_ERR) {

            write(STDERR, ERROR_SIGNAL_FAILED, string_len(ERROR_SIGNAL_FAILED));
            exit(1);

        }

        /*Process input redirection*/
        if (stage == 0 && job->infile_path != NULL){
            input_fd = open(job->infile_path, O_RDONLY);

            if(input_fd < 0){

                write(STDERR, ERROR_OPEN_FILE, string_len(ERROR_OPEN_FILE));
                _exit(1);
                
            }
            if (dup2(input_fd, STDIN) == -1) {

                write(STDERR, ERROR_DUP2_FAILED, string_len(ERROR_DUP2_FAILED));
                _exit(1);

            }
            if(close(input_fd) == -1){

                write(STDERR, ERROR_CLOSE_FAILED, string_len(ERROR_CLOSE_FAILED));
                _exit(1);

            }

        }else if(stage > 0){

            if(dup2(pipefd[(stage - 1) * 2], STDIN) == -1){

                write(STDERR, ERROR_DUP2_FAILED, string_len(ERROR_DUP2_FAILED));
                _exit(1);

            }

        }

        /*Process output redirection*/
        if(stage == job->num_stages - 1 && job->outfile_path != NULL){
            output_fd = open(job->outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if(output_fd < 0){

                write(STDERR, ERROR_OPEN_FILE, string_len(ERROR_OPEN_FILE));
                _exit(1);

            }

            if(dup2(output_fd, STDOUT) == -1){

                write(STDERR, ERROR_DUP2_FAILED, string_len(ERROR_DUP2_FAILED));
                _exit(1); 

            }
            if(close(output_fd) == -1){
                
                write(STDERR, ERROR_CLOSE_FAILED, string_len(ERROR_CLOSE_FAILED));
                _exit(1);

            }
        }else if(stage < job->num_stages - 1){

            if(dup2(pipefd[stage * 2 + 1], STDOUT) == -1){

                write(STDERR, ERROR_DUP2_FAILED, string_len(ERROR_DUP2_FAILED));
                _exit(1);

            }

        }

        /*Close childs file descriptors*/
        for (i = 0; i < (job->num_stages -1) * 2; i++){
            
            if(close(pipefd[i]) == -1){
                
                write(STDERR, ERROR_CLOSE_FAILED, string_len(ERROR_CLOSE_FAILED));
                exit(1);

            }
        }

        /*Execute current stages command*/
        if(execve(job->pipeline[stage].argv[0], job->pipeline[stage].argv, NULL) == -1){

            write(STDERR, ERROR_EXECVE, string_len(ERROR_EXECVE));
            _exit(1);

        }

    }else if(pid > 0){ /*Parent starts here*/

        return pid;

    } 

}
