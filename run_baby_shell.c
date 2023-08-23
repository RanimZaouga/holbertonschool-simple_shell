#include "shell.h"
#define MAX_INPUT_LENGTH 100

/**
 * execute_command - Execute the given command as a child process using execvp.
 *
 * This function creates a child process using fork and attempts to execute
 * the specified command using the execvp system call. It waits for the child
 * process to complete and provides information about the exit status or
 * termination signal.
 *
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        perror("fork"); /* Handle fork error */
    }
    else if (child_pid == 0)
    {
        /* Child process */
        char *args[] = {NULL, NULL}; /* Create an array for execvp */
        args[0] = (char *)command; /* Assign the command to the first element */
        execve(command, args, NULL);
        
        perror("execve"); /* Handle execve error */
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }
    }
}


/*
 * run_shell - A simple Unix command line interpreter
 *
 * This program implements a basic Unix shell that reads commands from the user,
 * executes them if they are valid executables, and repeats the process until the
 * user enters the "end of file" (Ctrl+D) signal. The shell supports simple,
 * one-word commands without arguments.
 */
void run_shell()
/* Run the shell loop */
{
    char input[MAX_INPUT_LENGTH];
    
    while (1)
    {
        printf("simple_shell> "); /* Display shell prompt */
        
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\nExiting the shell.\n"); /* Handle Ctrl+D (EOF) */
                break;
            }
            perror("fgets"); /* Handle fgets error */
            continue;
        }
        
        input[strcspn(input, "\n")] = '\0'; /* Remove newline character */
        
        execute_command(input); /* Execute the entered command */
    }
}

int main(void)
{
    run_shell(); /* Start the shell */
    return (0);
}
