#ifndef SHELL_H
#define SHELL_H


extern char **environ;

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stddef.h>
#include <wait.h>
#include <stddef.h>
#include <errno.h>
#include <dirent.h>

/* Struct to hold shell-related information */
typedef struct
{
	char **argv;   /* Argument vector for the current command */
	char *path;    /* Path of the executable */
	int status;    /* Status of the command execution */
} info_t;

int main(void);
void run_shell(void);

#endif
