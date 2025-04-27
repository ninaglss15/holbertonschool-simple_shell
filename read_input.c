#include "shell.h"

/**
* read_input - read a line from standard input
*
* Description : lit une ligne propre, gère EOF, prépare ligne pour tokenize
* Return: pointer to the read line, or NULL on EOF
*/

char *read_input(void)
{
	char *line = NULL; /* va contenir ligne lue */
	size_t len = 0; /* taille */
	ssize_t nread; /* résultat de getline : nb de ch. lus */

	nread = getline(&line, &len, stdin); /* lit depuis stdin, alloc auto mem */

	if (nread == -1) /* si erreur ou Ctrl + D (EOF) */
	{
		free(line);
		return (NULL); /* retrourne NULL pour break shell */
	}

	trim_spaces(line);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	/* boucle nettoie espaces blancs en FIN de ligne */
	while (nread > 0 && (line[nread - 1] == '\n' || line[nread - 1] == ' '
			|| line[nread - 1] == '\t' || line[nread - 1] == '\r'))
	{
		line[nread - 1] = '\0'; /* remplace par \0 */
		nread--; /* on réduit de 1 pour vérifier ch. prev */
	}

	if (nread == 0) /* cas extrême : ligne contient que espaces blancs */
	{
		free(line);
		return (NULL);
	}

	return (line); /* ligne nettoyée et prête à être analysée */
}
