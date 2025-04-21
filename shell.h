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
#define NOT_FOUND_ERROR 127
#define PERMISSION_ERROR 126

extern char **environ;
extern int command_count;

/* Prompt and input functions */
void display_prompt(void);
char *read_input(void);
int is_empty(const char *str);

/* Command parasing */

char **tokenize_input(char *line);
void free_tokens(char **tokens);

/* Path resolution */
char *find_command_path(const char *cmd);
char *check_executable(const char *path);
char *search_in_path(const char *cmd, char *path_copy);

/* Execution */
void execute_command(char *cmd, char *prog_name);
void execute_in_child(char *cmd_path, char **args, char *prog_name);
void handle_command_error(char *prog_name, char **args);
void handle_fork_error(char *cmd_path, char **args, char *prog_name);
void handle_parent_process(pid_t pid, char *cmd_path, char **args);

/* Built-in commands */
int handle_builtin(char **args, char *line);
int handle_env(char **args, char *line);

#endif /* SHELL_H */
