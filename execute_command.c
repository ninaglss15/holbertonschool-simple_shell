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
	char *cmd_path;

	args = tokenize_input(cmd);
	if (!args || args[0] == NULL)
	{
		if (args)
			free_tokens(args);
		return;
	}

	if (handle_builtin(args, cmd))
		return;

	cmd_path = check_command(args, prog_name);
	if (!cmd_path)
		return;

	pid = fork();
	if (pid == -1)
	{
		handle_fork_error(cmd_path, args, prog_name);
		return;
	}

	if (pid == 0)
		execute_in_child(cmd_path, args, prog_name);
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		free_tokens(args);
	}
}

/**
 * launch_process - fork et exécute la commande via execve
 * @cmd_path: chemin complet de la commande
 * @args: tableau d'arguments
 * @prog_name: nom du programme pour les erreurs
 */

void launch_process(char *cmd_path, char **args, char *prog_name)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return;
	}

	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
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
