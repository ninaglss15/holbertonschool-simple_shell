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

void display_prompt(void);
char *read_input(void);

int _strlen(const char *s);

int is_empty(const char *str);

int _strcmp(const char *s1, const char *s2);

char **tokenize_input(char *line);

void free_tokens(char **tokens);

void execute_in_child(char **args, char *prog_name);

char *find_command_path(const char *cmd);

int handle_env(char **args, char *line);

int handle_builtin(char **args, char *line);

int execute_command(char **args, char **argv, int line_number, char *line);

int launch_process(char *path, char **args);


#endif
