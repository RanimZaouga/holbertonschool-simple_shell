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
typedef struct {
    char **argv;   /* Argument vector for the current command */
    char *path;    /* Path of the executable */
    int status;    /* Status of the command execution */
} info_t;

int main(void);
/* Clears the info struct */
void clear_info(info_t *info);

/* Sets information in the info struct */
void set_info(info_t *info, char **av);

/* Finds and executes built-in commands */
int find_builtin(info_t *info);

/* Finds and executes external commands */
void find_cmd(info_t *info);

/* Forks a child process to execute a command */
void fork_cmd(info_t *info);

/* Prints error messages */
void print_error(info_t *info, const char *message);

#endif