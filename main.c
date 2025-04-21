#include "shell.h"

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
	char **args = NULL;

	(void)argc;

	while (1)
	{
		display_prompt();

		line = read_input();
		if (line == NULL)
			break;

		if (!is_empty(line))
		{
			args = tokenize_input(line);
			if (args != NULL && args[0] != NULL)
			{
				if (!handle_builtin(args, line))
					execute_command(args, argv[0]);
			}
		}

		free(line);
	}

	return (0);
}
