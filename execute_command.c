#include "shell.h"

/**
 * execute_command - Gère l'exécution d'une commande
 * @args: tableau des arguments
 * @argv: tableau d'arguments du programme principal
 * @line_number: numéro de la ligne lue
 * @line: ligne brute entrée par l'utilisateur
 *
 * Return: 1 pour continuer, sinon code de retour d'erreur
 */

int execute_command(char **args, char **argv, int line_number, char *line)
{
	char *path;

	if (args[0] == NULL)
		return (1);

	if (handle_builtin(args, line))
		return (0);

	path = find_command_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			 argv[0], line_number, args[0]);
		return (127);
	}

	if (access(path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			 argv[0], line_number, args[0]);
		free(path);
		return (126);
	}

	return (launch_process(path, args));
}

/**
 * launch_process - Fork et exécute la commande avec execve
 * @path: chemin de la commande
 * @args: tableau d'arguments
 *
 * Return: 1 pour continuer la boucle principale
 */
int launch_process(char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (1);
	}

	if (pid == 0)
	{
		execve(path, args, environ);
		perror("execve");
		free(path);
		exit(EXIT_FAILURE);
	}
	else
		wait(&status);

	free(path);
	return (1);
}
