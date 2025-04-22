include "shell.h"

/**
 * is_empty - check if string is empty or contains only witepace * @str: string to check
 *
 * Return: 1 if empty, 0 otherwise
*/

int is_empty(const char *str)
{
        while (*str)
        {
                if (*str != ' ' && *str != '\t' && *str != '\n')
                        return (0);
                str++;
        }
        return (1);
}
