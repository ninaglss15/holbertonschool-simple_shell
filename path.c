#include "shell.h"

/**
* is_direct_path - check if a command is a direct path
* @cmd: order to check
*
* Return: file path if found, NULL otherwise
*/
char *is_direct_path(const char *cmd)
{
	struct stat st;

	if (strchr(cmd, '/')) /* vérifie si cmd contient '/' */
	{
		if (stat(cmd, &st) == 0) /* si le fichier existe */
			return (strdup(cmd)); /* retourne une copie du chemin */
		else
			return (NULL);
	}
	return (NULL);
}

/**
* get_path_env - retrieves the PATH variable from the environment
*
* Return: copy of the PATH variable or NULL if not found
*/
char *get_path_env(void)
{
	int i;

	char *path = NULL;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}
	return (path ? strdup(path) : NULL); /* retourne une copie de PATH */
}

/**
* search_in_path - searches for a command in the PATH directories
* @cmd: command to search
* @path_copy: copy the PATH variable
*
* Return: full path if found, NULL otherwise
*/
char *search_in_path(const char *cmd, char *path_copy)
{
	char *dir, *full_path;

	struct stat st;
	int len;

	dir = strtok(path_copy, ":"); /* découpe PATH en répertoires */
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2; /* longueur pour concaténation */
		full_path = malloc(len); /* allocation mémoire */
		if (!full_path)
			return (NULL);

		sprintf(full_path, "%s/%s", dir, cmd); /* construit le chemin complet */
		if (stat(full_path, &st) == 0) /* vérifie si le fichier existe */
			return (full_path); /* retourne le chemin trouvé */

		free(full_path); /* libère si le fichier n'existe pas */
		dir = strtok(NULL, ":"); /* passe au répertoire suivant */
	}
	return (NULL);
}

/**
* find_command_path - searches for the full path of a command in the PATH
* @cmd: command to search
*
* Return: full path if found, NULL otherwise
*/
char *find_command_path(const char *cmd)
{
	char *path, *path_copy, *result;

	if (!cmd || cmd[0] == '\0') /* vérifie si cmd est vide */
		return (NULL);

	result = is_direct_path(cmd); /* vérifie si cmd est un chemin direct */
	if (result)
		return (result);

	path = get_path_env(); /* récupère la variable PATH */
	if (!path)
		return (NULL);

	path_copy = strdup(path); /* copie PATH pour le modifier */
	free(path); /* libère la copie originale */
	if (!path_copy)
		return (NULL);

	result = search_in_path(cmd, path_copy); /* cherche dans les répertoires */
	free(path_copy); /* libère la copie modifiée */
	return (result); /* retourne le chemin trouvé ou NULL */
}
