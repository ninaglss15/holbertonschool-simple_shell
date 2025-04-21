#include "shell.h"

/**
* execute_command - execute a command
* @cmd: command to execute
* @prog_name: program name for error messages
*/

void execute_command(char *cmd, char *prog_name)
{
	pid_t pid;
	char **args;
	char *cmd_path = NULL;

	args = tokenize_input(cmd);
	if (args == NULL || args[0] == NULL)
	{
		if (args)
			free_tokens(args);
		return;
	}

	if (handle_builtin(args, cmd))
		return;

	cmd_path = find_command_path(args[0]);
	if (!cmd_path)
	{
		handle_command_error(prog_name, args);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		handle_fork_error(prog_name, cmd_path, args);
		return;
	}

	if (pid == 0)
		execute_in_child(cmd_path, args, prog_name);
	else
		handle_parent_process(pid, cmd_path, args);
}


/**
 * check_command - checks if a command exists and returns its path
 * @args: array of arguments, where args[0] is the command
 * @prog_name: program name for error messages
 *
 * Return: the full path of the command if found, NULL otherwise
 */

char *check_command(char **args, char *prog_name)
{
	char *cmd_path = find_command_path(args[0]);

	if (!cmd_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
	}

	return (cmd_path);
}


/**
 * handle_fork_error - handles errors during fork
 * @cmd_path: path to the command
 * @args: array of arguments
 * @prog_name: program name for error messages
 */

void handle_fork_error(char *cmd_path, char **args, char *prog_name)
{
	perror(prog_name);
	free(cmd_path);
	free_tokens(args);
}
