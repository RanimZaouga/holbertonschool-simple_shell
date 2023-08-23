#include "shell.h"

#define MAX_INPUT_LENGTH 100

int main(void)
{
    info_t info;
    char *av[] = {"simple_shell", NULL}; /* Argument vector for the shell itself */

    while (1)
	{
        info.argv = NULL;
        printf("$ ");
        ssize_t r = getline(&(info.argv), &(size_t){0}, stdin);
        if (r == -1)
		{
            if (feof(stdin))
			{
                printf("\n"); /* Print newline after Ctrl+D */
                free(info.argv);
                break;
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }
        info.argv[r - 1] = NULL; /* Remove newline */

        if (!info.argv[0])
		{
            free(info.argv);
            continue; /* Empty line */
        }

        set_info(&info, av);
        if (!find_builtin(&info))
		{
            find_cmd(&info);
        }

        free_info(&info, 1);
    }

    return (EXIT_SUCCESS);
}
