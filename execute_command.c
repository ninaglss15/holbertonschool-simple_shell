#include "shell.h"

/**
* execute_command - execute a command
* @cmd: command to execute
* @prog_name: program name for error messages
*/

void execute_command(char *cmd, char *prog_name)
{
	char **args, *cmd_path;

	args = tokenize_input(cmd);
	if (!args || args[0] == NULL)
	{
		if (args)
			free_tokens(args);
		return;
	}

	if (handle_builtin(args, cmd))
	{
		free_tokens(args);
		return;
	}

	cmd_path = find_command_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		return;
	}

	launch_process(cmd_path, args, prog_name);
	free(cmd_path);
	free_tokens(args);
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
		wait(&status);
	}
}
