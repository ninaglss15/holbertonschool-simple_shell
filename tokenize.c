#include "shell.h"

/**
* tokenize_input - split input line into command and arguments
* @line: line to tokenize
*
* Description: transforme ligne de cmd en tableau de mots
* Return: array of tokens
*/

char **tokenize_input(char *line) /* reçoit une entrée par l'user */
{
	char **tokens = malloc(sizeof(char *) * MAX_ARGS); /* alloc jsq max args */
	char *token; /* pointe vers chaque mot extrait */
	int i = 0;

	if (!tokens) /* vérif si succès malloc */
		return (NULL);

	while (*line && (*line == ' ' || *line == '\t'
			|| *line == '\n' || *line == '\r')) /* saute espaces DEBUT ligne */
		line++;

	token = strtok(line, " \t\n\r"); /* pour découper selon séparateurs */
	while (token && i < MAX_ARGS - 1) /* on trouve mot et dépasse pas max */
	{
		tokens[i] = strdup(token); /* copie mot ds tableau */
		if (!tokens[i]) /* vérif erreur alloc */
		{
			free_tokens(tokens);
			return (NULL);
		}
		token = strtok(NULL, " \t\n\r"); /* on finit mot avec NULL */
		i++; /* next word */
	}
	tokens[i] = NULL; /* termine tableau avec NULL, comme exigé par execve */

	return (tokens); /* tableau final prêt */
}

/**
* free_tokens - free memory allocated for tokens
*
* Description: ds tokenize alloc pour chaque token,
* donc on libère chaque tokens[i] quand plus besoin
* @tokens: array of tokens to free
*/

void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]); /* chaque tokens[i] */

	free(tokens); /* puis tableau lui_même */
}
