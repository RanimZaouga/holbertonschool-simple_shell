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
        perror("fork");
    }
    else if (child_pid == 0)
    {
        // Child process
        char *args[] = {command, NULL}; // Create an argv array for execvp
        execvp(command, args);
        
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
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

/* Run the shell loop */
void run_shell(void)
{
    char command[MAX_INPUT_LENGTH];
    while (1)
    {
        printf("simple_shell> ");
        if (fgets(command, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            printf("Exiting...\n");
            break;
        }

        /* Remove newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        /* Check if command is empty */
        if (strcmp(command, "") == 0)
        {
            continue;
        }

        /* Check if command is a valid executable */
        if (access(command, X_OK) != 0)
        {
            printf("Error: '%s' is not a valid executable.\n", command);
            continue;
        }

        /* Execute command */
        if (fork() == 0)
        {
            execl(command, command, NULL); /* Execute with only the command itself as an argument */
            perror("Error");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
}

int main(void)
{
    run_shell(); /* Start the shell */
    return (0);
}