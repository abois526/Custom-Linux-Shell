/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   parse.c
/
/  Program Purpose(s):
/    Functions to parse user input and break it into commands 
/    which are placed into the job struct to be ran in the shell.
/---------------------------------------------------------*/

#include <sys/types.h>
#include "jobs.h"
#include "parse.h"
#include "commands.h"
#include "globals.h"
#include "stringlib.h"

/*---------- FUNCTION: parse_command -----------------------
/  PURPOSE:
/    Parses the array of tokens to populate the Command and Job 
/    structs with info, including command args and I/O redirection paths.
/  
/  CALLER INPUT:
/    Command *command
/      - A pointer to a Command struct within the job struct.
/    char *tokens[]
/      - An array of strings that contains the tokenized input from the user.
/    Job *job
/      - A pointer to a Job struct.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the tokens array is properly formatted and null-terminated.
/    - Assumes that command->argv has enough space to store all command-line 
/      arguments.
/---------------------------------------------------------*/
void parse_command(Command *command, char *tokens[], Job *job){

    int i = 0;
    command->argc = 0;

    while(tokens[i] != NULL){

        if(string_comp(tokens[i], "<") == 0){
            job->infile_path = tokens[i + 1];
            i += 2;

        }else if(string_comp(tokens[i], ">") == 0){

            job->outfile_path = tokens[i + 1];
            i += 2;

            
        }else if(string_comp(tokens[i], "&") == 0){
           
            job->background = 1;
            i++;
            
        }else{

            command->argv[command->argc++] = tokens[i];
            i++;
        }
    }

    command->argv[command->argc] = NULL;

}

/*---------- FUNCTION: parse_pipeline ----------------------
/  PURPOSE:
/    Parses an array of tokens to build a pipeline of commands
/    splitting the commands at pipe symbols.
/  
/  CALLER INPUT:
/    Job *job
/      - A pointer to a Job struct.
/    char *tokens[]
/      - An array of strings that contains the tokenized input from the user.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the tokens array is properly formatted and 
/      null-terminated.
/---------------------------------------------------------*/
void parse_pipeline(Job *job, char *tokens[]){

    int stage = 0;
    int start = 0;
    int i;

    for(i = 0; tokens[i] != NULL; i++){

        if(string_comp(tokens[i], "|") == 0){
            
            tokens[i] = NULL; /*Splits stages*/
            parse_command(&job->pipeline[stage], &tokens[start], job);
            stage++;
            start = i + 1;

        }
    }
    
    if(tokens[start] != NULL){

        parse_command(&job->pipeline[stage], &tokens[start], job);
        stage++;
    }

    job->num_stages = stage;

}

/*---------- FUNCTION: parse_job ---------------------------
/  PURPOSE:
/    Parses a job by getting a command from user input and 
/    then builds the pipeline of commands based on the input.
/  
/  CALLER INPUT:
/    Job *job
/      - A pointer to a Job struct.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Assumes that the job struct is properly initialized.
/---------------------------------------------------------*/
void parse_job(Job *job){

    char *tokens[MAX_ARGS];

    get_command(tokens);

    if (tokens[0] == NULL || tokens[0][0] == '\0'){
        return;
    }

    parse_pipeline(job, tokens);
    
}