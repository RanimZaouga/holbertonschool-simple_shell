#include "shell.h"

#define MAX_INPUT_LENGTH 100

int main() {
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
