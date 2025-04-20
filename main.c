#include "shell.h"

/**
 * main - entry point of the shell
 * @argc: number of arguments
 * @argv: array of arguments
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

		execute_command(line, argv[0]);
		free(line);
	}

	return (0);
}
