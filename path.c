#include "shell.h"

/**
* check_executable - checks if a given path is an executable file
* @path: file path to check
*
* Return: duplicate of the path if it is executable, NULL otherwise
*/

char *check_executable(const char *path)
{
	struct stat buffer;

	if (stat(path, &buffer) == 0)
	{
		if (S_ISREG(buffer.st_mode) && (buffer.st_mode & S_IXUSR))
			return (strdup(path));
	}
	return (NULL);
}

/**
* search_in_path - searches for a command in the given PATH
* @cmd: command to search for
* @path_copy: copy of the PATH environment variable
*
* Return: full path of the command if found, NULL otherwise
*/
char *search_in_path(const char *cmd, char *path_copy)
{
	char *path_token = strtok(path_copy, ":");
	char *full_path = NULL;
	char *result;

	while (path_token)
	{
		full_path = malloc(strlen(path_token) + strlen(cmd) + 2);
		sprintf(full_path, "%s/%s", path_token, cmd);

		result = check_executable(full_path);

		if (result)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		path_token = strtok(NULL, ":");
	}
	return (NULL);
}

/**
* find_command_path - searches the full path of a command in the PATH
* @cmd: Command to search for
*
* Return: full path if found, NULL otherwise (to be freed)
*/

char *find_command_path(const char *cmd)
{
	char *path;
	char *path_copy;
	char *result;

	if (cmd == NULL || cmd == NULL)
		return (NULL);

	if (strchr(cmd, '/'))
		return (check_executable(cmd));

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	result = search_in_path(cmd, path_copy);

	free(path_copy);
	return (result);
}
