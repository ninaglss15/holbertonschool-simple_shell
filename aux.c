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

/**
 * is_empty - check if string is empty or contains only witepace
 * @str: string to check
 *
 * Return: 1 if empty, 0 otherwise
*/

int is_empty(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

/**
 * _strcmp - compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if strings are equal, non-zero otherwise
*/

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	if (!s1 || !s2)
		return (1);

	while (s1[i] != s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}
