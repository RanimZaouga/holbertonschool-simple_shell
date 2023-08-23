#include "shell.h"

#define MAX_INPUT_LENGTH 100
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