#include "shell.h"

/**
* execute_command - execute a command
* @cmd: command to execute
* @prog_name: program name for error messages
*/

void execute_command(char *cmd, char *prog_name)
{
	pid_t pid;
	int status;
	char **args;

	args = tokenize_input(cmd);
	if (!args || args[0] == NULL)
	{
		if (args)
			free_tokens(args);
		return;
	}

	if (_strcmp(cmd, "exit") == 0)
		exit(EXIT_SUCCESS);

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free_tokens(args);
		return;
	}

	if (pid == 0)
		execute_in_child(args, prog_name);
	else
	{
		wait(&status);
		free_tokens(args);
	}
}

/**
 * execute_in_child - execute command in child precess
 * @args: array of command and arguments
 * @prog_name: program name for error messages
 */

void execute_in_child(char **args, char *prog_name)
{
	if (execve(args[0], args, environ) == -1)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		exit(EXIT_FAILURE);
	}
}
