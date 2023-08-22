#include "shell.h"

#define MAX_INPUT_LENGTH 100

void execute_command(const char *command)
/**
 * execute_command - Execute the given command as a child process.
 *
 * @command: The command to execute.
 */
{
	pid_t child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork"); /* Handle fork error */
	}
	else if (child_pid == 0) {
		/* Child process */
		if (execlp(command, command, NULL) == -1)
		{
			perror("execlp"); /* Handle execlp error */
			exit(EXIT_FAILURE); /* Exit child process with error status */
		}
	}
	else
	{
		/* Parent process */
		int status;
		waitpid(child_pid, &status, 0); /* Wait for child process to complete */
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


void run_shell() 
/**
 * run_shell - Run the shell's main loop.
 */
{
	char input[MAX_INPUT_LENGTH];
	
	while (1) {
		printf("simple_shell> "); /* Display prompt */
		
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
