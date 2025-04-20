#include "shell.h"

/**
* read_input - read a line from standard input
*
* Return: pointer to the read line, or NULL on EOF
*/

char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	while (nread > 0 && (line[nread - 1] == '\n' || line[nread - 1] == ' '
			|| line[nread - 1] == '\t' || line[nread - 1] == '\r'))
	{
		line[nread - 1] = '\0';
		nread--;
	}

	if (nread == 0)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
