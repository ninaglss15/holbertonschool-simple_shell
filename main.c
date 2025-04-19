#include "shell.h"

/**
 * main - entry point of the shell
 *
 * Return: 0 for success
 */

int main(void)
{
	char *line = NULL;

	while (1)
	{
		display_prompt();

		line = read_input();
		if (line == NULL)
			break;

		execute_command(line);
		free(line);
	}

	return (0);
}
