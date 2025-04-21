#include "shell.h"
/**
* execute_in_child - execute command in child process
* @cmd_path: path to the command to be executed
* @args: array of command and arguments
* @prog_name: program name for error messages
*/

void execute_in_child(char *cmd_path, char **args, char *prog_name)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		perror(prog_name);
		free(cmd_path);
		free_tokens(args);
		exit(EXIT_FAILURE);
	}
}
