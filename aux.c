#include "shell.h"

/**
* is_empty - check if string is empty or contains only witepace
* @str: string to check
*
* Description : vérifie seulement si contient
* Return: 1 if empty, 0 otherwise
*/

int is_empty(const char *str)
{
	while (*str) /* tant que str != \0 */
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0); /* si autre ch. alors non vide dc next fonction */
		str++; /* next ch. */
	}
	return (1); /* \0 atteint sans ch. utile */
}

/**
* trim_spaces - removes leading and trailing whitespace from a string
* @str: the string to be trimmed
*
* Description: this function modifies the input string in place by
* removing any leading or trailing spaces, tabs, newlines, or carriage returns
*/
void trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t'
			|| *str == '\n' || *str == '\r')
		str++;

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		*end-- = '\0';
}
