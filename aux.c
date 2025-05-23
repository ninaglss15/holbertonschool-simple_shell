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
	char *start = str;
	char *end;

	while (*start == ' ' || *start == '\t' ||
		   *start == '\n' || *start == '\r')
		start++;

	if (*start == '\0')
	{
		*str = '\0';
		return;
	}

	end = start + strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'
			|| *end == '\n' || *end == '\r'))
		*end-- = '\0';

	while (*start)
		*str++ = *start++;
	*str = '\0';
}
