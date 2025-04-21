#include "shell.h"

/**
* get_command_path - find pull path of command in PATH
* @command: command to search
*
* Return: full path if found, NULL otherwise
*/

char *get_command_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy, *dir, *full_path;

	if (!path || command[0] == '/')
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
