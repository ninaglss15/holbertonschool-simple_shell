#include "shell.h"

/**
* tokenize_input - split input line into command and arguments
* @line: line to tokenize
*
* Return: array of tokens
*/

char **tokenize_input(char *line)
{
	char **tokens = malloc(sizeof(char *) * MAX_ARGS);
	char *token;
	int i = 0;

	if (!tokens)
		return (NULL);

	while (*line && (*line == ' ' || *line == '\t'
			|| *line == '\n' || *line == '\r'))
		line++;

	token = strtok(line, " \t\n\r");
	while (token && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			free_tokens(tokens);
			return (NULL);
		}
		token = strtok(NULL, " \t\n\r");
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
* free_tokens - free memory allocated for tokens
* @tokens: array of tokens to free
*/

void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i]; i++)
		free(tokens[i]);

	free(tokens);
}

