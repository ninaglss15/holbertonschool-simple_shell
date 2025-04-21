#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
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
char **copy_args(char **original);

/* Command parasing */
char **tokenize_input(char *line);
void free_tokens(char **tokens);

/* Path resolution */
void execute_command(char **args, char *prog_name);
char *get_command_path(char *command);

/* Built-in commands */
int handle_builtin(char **args, char *line);
int handle_env(char **args, char *line);

#endif /* SHELL_H */
