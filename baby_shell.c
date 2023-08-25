#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * run_shell - Run a simple Unix command line interpreter (baby shell).
 *
 * This function implements a basic Unix shell
 * that reads commands from the user,
 * executes them if they are valid executables,
 * and repeats the process until the
 * user enters the "exit" command.
 * The shell supports simple one-word commands without arguments.
 * It displays a prompt, waits for user input,
 * and provides error messages for invalid inputs
 * and non-executable commands.
 */
void run_shell(void)
{
	char command[100];
	pid_t pid;

	while (1)
	{
			printf("simple_shell> "); /* Display shell prompt */

			/* Read user input */
			scanf("%s", command);

			/* Check if user entered "exit" command */
			if (strcmp(command, "exit") == 0)
		{
		break; /* Exit the shell */
		}

		/* Create a child process */
		pid = fork();

		if (pid == 0)
		{
			/* Child process */
			execlp(command, command, NULL); /* Execute the command */
			perror("Error"); /* Handle exec error */
			exit(1); /* Exit child process with error status */
		}
		else if (pid > 0)
		{
			/* Parent process */
			wait(NULL); /* Wait for child process to complete */
		}
		else
		{
			/* Fork error */
		   perror("Error"); /* Handle fork error */
		   exit(1); /* Exit with error status */
		}
   }
}
