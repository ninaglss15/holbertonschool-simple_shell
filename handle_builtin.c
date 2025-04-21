#include "shell.h"

/**
 * handle_builtin - gère les commandes internes comme "exit" et "env"
 * @args: tableau de mots (ex: args[0] = "exit", args[1] = NULL, etc.)
 * @line: ligne complète à libérer en cas de "exit"
 *
 * Return: 1 si une commande builtin a été trouvée et exécutée, 0 sinon
 */

int handle_builtin(char **args, char *line)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		free(line);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
		return (handle_env(args, line));

	return (0);
}


/**
 * handle_env - handles the "env" command to print environment variables
 * @args: array of words (e.g., args[0] = "env", args[1] = NULL, etc.)
 * @line: complete line (unused in this function)
 *
 * Return: 1 if the "env" command is executed, 0 otherwise
 */

int handle_env(char **args, char *line)
{
	int i = 0;

	(void)line;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	free_tokens(args);
	return (1);
}
