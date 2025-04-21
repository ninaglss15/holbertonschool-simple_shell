#include "shell.h"


/**
 * is_empty - check if string is empty or contains only witepace
 * @str: string to check
 *
 * Return: 1 if empty, 0 otherwise
 */

int is_empty(const char *str)
{
	int i = 0;

	if (!str)
		return (1);

	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' &&
			str[i] != '\n' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

/**
 * copy_args - creates a copy of an array of strings
 * @original: the original array of strings to copy
 *
 * Return: a pointer to the newly allocated copy of the array
 */

char **copy_args(char **original)
{
	int count = 0;
	char **copy;
	int i;

	if (original == NULL)
		return (NULL);

	while (original[count])
		count++;

	copy = malloc((count + 1) * sizeof(char *));
	if (copy == NULL)
		return (NULL);

	for (i = 0; i < count; i++)
	{
		copy[i] = strdup(original[i]);
		if (copy[i] == NULL)
		{
			free_tokens(copy);
			return (NULL);
		}
	}
	copy[count] = NULL;
	return (copy);
}
