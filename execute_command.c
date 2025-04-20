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
	struct stat st;
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	if (stat(cmd, &st) != 0 || !(st.st_mode & S_IXUSR))
	{
		fprintf(stderr, "%s: No such file or directory\n", prog_name);
		return;
	}

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
