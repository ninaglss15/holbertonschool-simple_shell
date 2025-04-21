#include "shell.h"

/**
* validate_and_resolve_command - Check command validity and resolve path
* @args: Array of command and arguments
* @prog_name: Program name for error messages
* Return: Resolved command path or NULL
*/

static char *validate_and_resolve_command(char **args, char *prog_name)
{
	struct stat st;
	char *path;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
			return (strdup(args[0]));
	}
	else
	{
		path = get_command_path(args[0]);

		if (path)
			return (path);
	}

	fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
	return (NULL);
}


/**
* execute_command - main command execution flow
* @args: array of command and arguments
* @prog_name: program name for error messages
*/

void execute_command(char **args, char *prog_name)
{
	char *resolved_cmd;
	pid_t pid;
	char **args_copy;

	if (!args || !args[0])
		return;

	resolved_cmd = validate_and_resolve_command(args, prog_name);
	if (!resolved_cmd)
		return;

	args_copy = copy_args(args);
	free(args_copy[0]);
	args_copy[0] = resolved_cmd;

	pid = fork();

	if (pid == 0)
	{
		execve(args_copy[0], args_copy, environ);
		perror(prog_name);
		_exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		free_tokens(args_copy);
	}
}
