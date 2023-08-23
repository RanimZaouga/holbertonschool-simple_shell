#include "shell.h"
/*
 * main - A simple Unix command line interpreter (baby shell)
 *
 * This program implements a basic Unix shell that reads commands from the user,
 * executes them if they are valid executables, and repeats the process until the
 * user enters the "end of file" (Ctrl+D) signal. The shell supports simple,
 * one-word commands without arguments. It displays a prompt, waits for user input,
 * and provides simple error messages for invalid inputs and non-executable commands.
 *
 * Features:
 * - Displays a prompt for user input
 * - Executes valid executable commands
 * - Handles "end of file" condition (Ctrl+D)
 * - Provides error messages for invalid commands
 * - Supports one-word commands without arguments
 */
 
int main(void)
{
    char command[1024];
    while (1)
	{
        printf("simple_shell> ");
        fgets(command, 1024, stdin);
        /* Check if user entered "end of file" (Ctrl+D) */
        if (strcmp(command, "EOF\n") == 0)
		{
            printf("Exiting...\n");
            break;
        }
        /* Check if command is empty */
        if (strcmp(command, "\n") == 0)
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
            execve(command, NULL, NULL);
            perror("Error");
            exit(1);
        }
		else
		{
            wait(NULL);
        }
    }
    return (0);
}
