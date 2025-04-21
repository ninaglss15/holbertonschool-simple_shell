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

	 char **args;

	 int line_number = 0;

	 (void)argc;

	while (1)
	{
		display_prompt();

		line = read_input();
		if (line == NULL)
			break;

		if (!is_empty(line))
		{
			line_number++;
			args = tokenize_input(line);
		if (args)
		{
			execute_command(args, argv, line_number, line);
			free(args);
		}
		}

		 free(line);
	}

	return (0);
}
