#include "shell.h"

/**
* execute_in_child - execute command in child process
* @cmd_path: path to the command to be executed
* @args: array of command and arguments
* @prog_name: program name for error messages
*/

void execute_in_child(char *cmd_path, char **args, char *prog_name)
{
	execve(cmd_path, args, environ);
	fprintf(stderr, "%s: %d: %s: Permission denied\n",
			prog_name, command_count, args[0]);
	free(cmd_path);
	free_tokens(args);
	exit(PERMISSION_ERROR);
}

/**
* handle_command_error - handles errors when a command is not found
* @prog_name: program name for error messages
* @args: array of command and arguments
*/
void handle_command_error(char *prog_name, char **args)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, command_count, args[0]);
	free_tokens(args);
	command_count++;
}

/**
* handle_fork_error - handles errors that occur during fork
* @prog_name: program name for error messages
* @cmd_path: path to the command to be executed
* @args: array of command and arguments
*/
void handle_fork_error(char *prog_name, char *cmd_path, char **args)
{
	perror(prog_name);
	free(cmd_path);
	free_tokens(args);
	command_count++;
}

/**
* handle_parent_process - handles the parent process after forking
* @pid: process ID of the child
* @cmd_path: path to the command to be executed
* @args: array of command and arguments
*/
void handle_parent_process(pid_t pid, char *cmd_path, char **args)
{
	int status;

	waitpid(pid, &status, 0);
	free(cmd_path);
	free_tokens(args);
	command_count++;
}
