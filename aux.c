#include "shell.h"

/**
 * _strlen - calculate the length of a string
 * @s: string to measure
 *
 * Return: length of the string
*/

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}
