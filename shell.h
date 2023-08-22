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

/* Function declarations */
void run_shell();

#endif