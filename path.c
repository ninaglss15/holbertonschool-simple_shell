#include "shell.h"

/**
 * find_command_path - cherche le chemin complet d'une commande dans le PATH
 * @cmd: commande à rechercher
 *
 * Return: chemin complet si trouvé NULL sinon (à libérer)
 */

char *find_command_path(const char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat st;
	int cmd_len, dir_len;

	if (!cmd)
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (stat(cmd, &st) == 0 && (st.st_mode & S_IXUSR))
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

	cmd_len = strlen(cmd);
	path_token = strtok(path_copy, ":");
	while (path_token)
	{
		dir_len = strlen(path_token);
		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, cmd);

		if (stat(file_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (file_path);
		}

		free(file_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
