#include "shell.h"
/**
 * main - Entry point for the simple Unix command line interpreter (baby shell).
 *
 * This program implements a basic Unix shell that
 * reads commands from the user,executes them if they are valid executables,
 * and repeats the process until the
 * user enters the "exit" command.
 * The shell supports simple one-word commands without arguments.
 * It displays a prompt, waits for user input,
 * and provides error messages for invalid inputs
 * and non-executable commands.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
/* Entry point of the program */
int main()
{
	run_shell(); /* Start the shell */
	return (0); /* Return success status */
}
