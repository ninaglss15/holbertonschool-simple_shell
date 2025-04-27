#include "shell.h"

/**
 * find_command_path - cherche le chemin complet d'une commande dans le PATH
 * @cmd: commande à rechercher
 *
 * Description: cherche le chemin complet d'une cmd
 * Return: chemin complet si trouvé NULL sinon (à libérer)
 */
char *find_command_path(const char *cmd)
{ /* contient contenu var d'env $PATH ; copie modifiable de PATH */
	char *path, *path_copy, *dir; /* rep courant extrait de $PATH */
	char *full_path; /* stockage chemin complet */
	struct stat st; /* pour savoir si fichier existe */
	int len; /* len nécessaire pour alloc full_path */
	int i;

	if (!cmd || cmd[0] == '\0') /* vérif si pas vide */
		return (NULL);

	if (strchr(cmd, '/')) /* vérifi si chemin contient / déjà chemin ? */
	{
		if (stat(cmd, &st) == 0) /* si existe */
			return (strdup(cmd)); /* retourne copie */
		else
			return (NULL);
	}

	for (i = 0 ; environ[i] ; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}
	if (!path) /* vérif pas vide */
		return (NULL);

	path_copy = strdup(path); /* duplique car strtok modifie chaîne */
	if (!path_copy) /* vérif pas vide */
		return (NULL);

	dir = strtok(path_copy, ":"); /* on découpe en morceaux selon séparateur */
	while (dir) /* calcule len pour concaténer */
	{
		len = strlen(dir) + strlen(cmd) + 2; /* len dir + / + cmd + \0 */
		full_path = malloc(len); /* alloc memoire dynamiquement */
		if (!full_path) /* vérif si échec */
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd); /* construction chaîne */

		if (stat(full_path, &st) == 0) /* si chem corresp à fichier existant */
		{
			free(path_copy); /* libère car plus besoin */
			return (full_path); /* retourne ce chemin */
		}

		free(full_path); /* sinon, si fichier n'existe pas, libère qd même */
		dir = strtok(NULL, ":"); /* NULL pour continuer, next dir ds le PATH */
	}

	free(path_copy); /* sinon, si aucun chem corresp, libère qd même */
	return (NULL); /* renvoie NULL */
}
