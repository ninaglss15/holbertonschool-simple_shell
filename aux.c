#include "shell.h"

/**
 * _strlen - calculates length of a string
 * @s: string
 *
 * Return: length
*/

int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}
