#include "shell.h"
#include <ctype.h>

/**
* print_error - prints error if command not found
* @cmd: command failed
*/

void print_error(char *cmd)
{
	int i, printable = 1;

	char *program = "./hsh";

	for (i = 0 ; cmd[i] != '\0' ; i++)
	{
		if (!isprint(cmd[i]))
		{
			printable = 0;
			break;
		}
	}

	if (printable)
	{
		write(STDERR_FILENO, program, _strlen(program));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	}
}
