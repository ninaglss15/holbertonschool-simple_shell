#include "shell.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 for success
 */

int main(int argc, char **argv)
{
	char *line = NULL; /* ptr NULL vers ligne - getline puisse alloué memoire */

	(void)argc;

	while (1)  /* boucle infinie - Ctrl + D ou exit */
	{
		display_prompt(); /* affiche invite de cmd si isatty ok */

		line = read_input(); /* lit une ligne depuis stdin */
		if (line == NULL) /* si read retourne NULL = Ctrl + D */
			break; /* arrêt du shell proprement */

		if (!is_empty(line))
			execute_command(line, argv[0]); /* exécute cmd */

		free(line);
	}

	return (0); /* sortie normale du programme (success)*/
}
