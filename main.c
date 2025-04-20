#include "shell.h"

/**
 * is_empty - check if string is empty or contains only whitespace
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
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 for success
 */

int main(int argc, char **argv)
{
	char *line = NULL;

	(void)argc;

	while (1)
	{
		display_prompt();

		line = read_input();
		if (line == NULL)
			break;

		if (!is_empty(line))
			execute_command(line, argv[0]);

		free(line);
	}

	return (0);
}
