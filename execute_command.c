#include "shell.h"

/**
* execute_command - creates a child process to execute a command
* @cmd: user's command
*/

void execute_command(char *cmd, char *prog_name)
{
	pid_t pid;
	int status;

	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror(prog_name);
		return;
	}

	if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}
