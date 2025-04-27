#include "shell.h"

/**
 * handle_builtin - gère les commandes internes comme "exit" et "env"
 * @args: tableau de mots (ex: args[0] = "exit", args[1] = NULL, etc.)
 * @line: ligne complète à libérer en cas de "exit"
 *
 * Description: détecter si cmd est interne au shell
 * Return: 1 si une commande builtin a été trouvée et exécutée, 0 sinon
 */
int handle_builtin(char **args, char *line)
{
	int i;

	if (args == NULL || args[0] == NULL) /* vérif supp si ligne vide */
		return (0);

	if (strcmp(args[0], "exit") == 0) /* on compare à exit */
	{
		free(line); /* on libère tout */
		free_tokens(args);
		exit(0); /* et on quitte proprement shell */
	}

	if (strcmp(args[0], "env") == 0) /* on compare à env */
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]); /* affiche var d'env ligne par ligne */
		free_tokens(args);
		return (1); /* cmd bultin a été gérée */
	}

	return (0); /* si cmd aucun des 2, on continue pour chercher chemin cmd */
}
