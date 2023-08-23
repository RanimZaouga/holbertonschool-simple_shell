#include "shell.h"
/**
 * main - Entry point for the simple Unix command line interpreter (baby shell).
 *
 * This program implements a basic Unix shell that reads commands from the user,
 * executes them if they are valid executables, and repeats the process until the
 * user enters the "end of file" (Ctrl+D) signal. The shell supports simple,
 * one-word commands without arguments. It displays a prompt, waits for user input,
 * and provides simple error messages for invalid inputs and non-executable commands.
 *
 * @return Always returns 0 to indicate successful execution.
 */
int main(void)
{
    char command[MAX_INPUT_LENGTH];
    
    while (1)
    {
        printf("simple_shell> "); /* Display shell prompt */
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\nExiting...\n"); /* Handle Ctrl+D (EOF) */
                break;
            }
            perror("fgets"); /* Handle fgets error */
            continue;
        }

        /* Remove trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "") == 0)
        {
            continue; /* Empty command, continue to the next iteration */
        }

        pid_t child_pid = fork();
        if (child_pid < 0)
        {
            perror("fork"); /* Handle fork error */
        }
        else if (child_pid == 0)
        {
            /* Child process */
            if (execlp(command, command, NULL) == -1)
            {
                perror("exec"); /* Handle exec error */
                exit(EXIT_FAILURE);
            }
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
    
    return (0);
}
