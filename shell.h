#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_ARGS 64

extern char **environ;

/* Prompt and input functions */
void display_prompt(void);
char *read_input(void);
int is_empty(const char *str);

/* Command parasing and execution */
void execute_command(char *cmd, char *prog_name);
char **tokenize_input(char *line);
void free_tokens(char **tokens);
char *find_command_path(const char *cmd);

/* Command executing helpers */
void execute_in_child(char *cmd_path, char **args, char *prog_name);
char *check_command(char **args, char *prog_name);
void handle_fork_error(char *cmd_path, char **args, char *prog_name);
void launch_process(char *cmd_path, char **args, char *prog_name);

/* Built-in commands */
int handle_builtin(char **args, char *line);
int handle_env(char **args, char *line);

#endif /* SHELL_H */
