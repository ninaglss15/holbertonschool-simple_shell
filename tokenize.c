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
	char *line_copy;
	char *token;
	int i = 0;

	if (!line || strlen(line) == 0)
		return (NULL);

	line_copy = strdup(line);

	if (!tokens || !line_copy)
	{
		free(tokens);
		free(line_copy);
		return (NULL);
	}

	token = strtok(line_copy, " \t\n\r\a");
	while (token && i < MAX_ARGS - 1)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free_tokens(tokens);
			free(line_copy);
			return (NULL);
		}
		token = strtok(NULL, " \t\n\r\a");
		i++;
	}
	tokens[i] = NULL;
	free(line_copy);
	return (tokens);
}

/**
* free_tokens - frees memory allocated for an array of tokens
* @tokens: array of tokens to free
*/

void free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return;

	for (i = 0; tokens[i] != NULL; i++)
		free(tokens[i]);

	free(tokens);
}
