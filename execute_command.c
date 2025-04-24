#include "shell.h"

/**
* execute_command - execute a command
* @cmd: command to execute
* @prog_name: program name for error messages
*
* Description: prend une cmd tokenisée, vérif bultin,
* trouve chemin cmd, fork processus fils, délègue execution
*/

void execute_command(char *cmd, char *prog_name)
{
	pid_t pid; /* pour stocker PID du processus fils */
	int status; /* récupère code de retour du fils via wait */
	char **args; /* array de la cmd + args */
	char *cmd_path; /* pour chemin absolu */

	args = tokenize_input(cmd); /* envoie pour tokenization */
	if (!args || args[0] == NULL) /* vérif supplémentaire si vide */
	{
		if (args)
			free_tokens(args);
		return;
	}
	if (handle_builtin(args, cmd)) /* verif cmd intégrée */
		return;
	cmd_path = find_command_path(args[0]); /* résolution du chemin */
	if (!cmd_path) /* si cmd non trouvée */
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
		free_tokens(args);
		return;
	}
	pid = fork(); /* création processus fils */
	if (pid == -1) /* si échec (soucis mem)*/
	{
		perror(prog_name);
		free(cmd_path);
		free_tokens(args);
		return;
	}
	if (pid == 0) /* si dans le fils */
	{
		args[0] = cmd_path; /* on remplace par chemin complet */
		execute_in_child(args, prog_name); /* rempl proc courant par prog cmd*/
	}
	else /* si dans le père */
	{
		wait(&status); /* attend que fils termine */
		free(cmd_path);
		free_tokens(args);
	}
}
