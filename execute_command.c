#include "shell.h"

/**
* execute_command - execute a command
* @cmd: command to execute
* @prog_name: program name for error messages
*/

void execute_command(char *cmd, char *prog_name)
{
        pid_t pid;
        int status;
        char *argv[2];
	char *path_cmd;

        if (_strcmp(cmd, "exit") == 0)
                exit(EXIT_SUCCESS);

	path_cmd = find_command_path(cmd);
	if (!path_cmd)
	{
		write(STDERR_FILENO, prog_name, _strlen(prog_name));
		write(STDERR_FILENO, ": command not found\n", 21);
		return;
	}
	argv[0] = path_cmd;
	argv[1] = NULL;

        pid = fork();
	if (pid == -1)
        {
                perror(prog_name);
                free(path_cmd);
                return;
        }

        if (pid == 0)
	{
		if (execute_in_child(path_cmd, argv, environ) == -1);
		{
			perror(prog_name);
			free(path_cmd);
			exit(EXIT_FAILURE);
		}
	}
        else
        {
                wait(&status);
                free(path_cmd);
        }
}

/**
 * execute_in_child - execute command in child precess
 * @args: array of command and arguments
 * @prog_name: program name for error messages
 */

void execute_in_child(char **args, char *prog_name)
{
        if (execve(args[0], args, environ) == -1)
        {
                fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
                free_tokens(args);
                exit(EXIT_FAILURE);
        }
}
