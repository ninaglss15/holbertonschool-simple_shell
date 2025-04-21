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
