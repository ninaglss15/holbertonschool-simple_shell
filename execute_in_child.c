#include "shell.h"
/**
* execute_in_child - execute command in child process
* @args: array of command and arguments
* @prog_name: program name for error messages
*
* Description: le parent prep tout (execute_command),
* le fils doit trouver bon exécutable et lancer execve.
* Permet de gérer les erreurs sans planter le shell parent.
*/
void execute_in_child(char **args, char *prog_name)
{
	char *full_path = NULL; /* va contenir chem complet vers cmd */

	if (strchr(args[0], '/')) /* verif si contient / chem absolu ? */
		full_path = strdup(args[0]); /* on duplique pour stocker et tester */
	else
		full_path = find_command_path(args[0]); /* cherche chem complet */

	if (!full_path) /* si pas trouvé de chem valide */
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		exit(EXIT_FAILURE); /* quitte processus enfant */
	}

	if (execve(full_path, args, environ) == -1) /* tente execute cmd */
	{ /* si réussit process enfant est remplacé par nv programme */
		perror(prog_name); /* si échec, non-existant file, permission denied */
		free(full_path); /* on libère tout et on quitte */
		free_tokens(args);
		exit(EXIT_FAILURE);
	}

	free(full_path);
}
