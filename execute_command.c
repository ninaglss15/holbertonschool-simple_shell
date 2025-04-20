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

	if (_strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		exit(EXIT_SUCCESS);
	}

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
