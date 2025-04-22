#include "shell.h"

/**
* tokenize_input - split input line into command and arguments
* @line: line to tokenize
*
* Return: array of tokens
*/

char **tokenize_input(char *line)
{
        char **tokens = malloc(sizeof(char *) * MAX_ARGS);
        char *token;
        int i = 0;

        if (!tokens)
                return (NULL);

        while (*line && (*line == ' ' || *line == '\t'
                        || *line == '\n' || *line == '\r'))
                line++;

        token = strtok(line, " \t\n\r");
        while (token && i < MAX_ARGS - 1)
        {
                tokens[i] = token;
                token = strtok(NULL, " \t\n\r");
                i++;
        }
        tokens[i] = NULL;

        return (tokens);
}

/**
* free_tokens - free memory allocated for tokens
* @tokens: array of tokens to free
*/

void free_tokens(char **tokens)
{
        free(tokens);
}

/**
* split_line - splits a line into an array or arguments
* @line: the input line
*
* Return: array of arguments (NULL-terminated)
*/

char **split_line(char *line)
{
        size_t bufsize = 64, i = 0;
        char **tokens = malloc(bufsize * sizeof(char *));
        char *token;

        if (!tokens)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }

        token = strtok(line, " \t\r\n");
        while (token != NULL)
        {
                tokens[i++] = token;

                if (i >= bufsize)
                {
                        bufsize *= 2;
                        tokens = realloc(tokens, bufsize * sizeof(char*));
                        if (!tokens)
                        {
                                perror("realloc");
                                exit(EXIT_FAILURE);
                        }
                }
                token = strtok(NULL, " \t\r\n");
        }
        tokens[i] = NULL;
        return (tokens);
}
