#include "shell.h"
/**
* execute_in_child - execute command in child process
* @args: array of command and arguments
* @prog_name: program name for error messages
*/
void execute_in_child(char **args, char *prog_name)
{
	char *full_path = NULL;

	if (strchr(args[0], '/'))
		full_path = strdup(args[0]);
	else
		full_path = find_command_path(args[0]);

	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		exit(EXIT_FAILURE);
	}

	if (execve(full_path, args, environ) == -1)
	{
		perror(prog_name);
		free(full_path);
		free_tokens(args);
		exit(EXIT_FAILURE);
	}

	free(full_path);
}
