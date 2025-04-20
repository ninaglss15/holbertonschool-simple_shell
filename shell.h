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

extern char **environ;

void display_prompt(void);
char *read_input(void);
void execute_command(char *cmd, char *prog_name);
int _strlen(const char *s);
int is_empty(const char *str);

#endif /* SHELL_H */
