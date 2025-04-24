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
