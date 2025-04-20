#include "shell.h"
#include <stdlib.h>  /* pour exit */
#include <stdio.h>   /* pour printf */
#include <string.h>  /* pour strcmp */

/**
 * handle_builtin - gère les commandes internes comme "exit" et "env"
 * @args: tableau de mots (ex: args[0] = "exit", args[1] = NULL, etc.)
 * @line: ligne complète à libérer en cas de "exit"
 *
 * Return: 1 si une commande builtin a été trouvée et exécutée, 0 sinon
 */
int handle_builtin(char **args, char *line)
{
	int i;

	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		free_tokens(args);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

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
	int i;

	(void)line;

	if (args[0] && strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}
