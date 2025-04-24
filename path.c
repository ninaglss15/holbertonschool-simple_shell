#include "shell.h"

/**
 * find_command_path - cherche le chemin complet d'une commande dans le PATH
 * @cmd: commande à rechercher
 *
 * Return: chemin complet si trouvé NULL sinon (à libérer)
 */
char *find_command_path(const char *cmd)
{
	char *path, *path_copy, *dir;
	char *full_path;
	struct stat st;
	int len;

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);

		if (stat(full_path, &st) == 0)
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
