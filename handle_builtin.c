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
	(void)line;

	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
		exit(EXIT_SUCCESS);

	return (0);
}

/**
 * handle_env - Prints the environment variables
 * @args: Unused parameter
 * @line: Unused parameter
 *
 * Return: 1 after printing the environment variables
 */

int handle_env(char **args, char *line)
{
	int i;
	(void)line;
	(void)args;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);

	return (1);
}
