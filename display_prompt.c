#include "shell.h"

/**
* display_prompt - display the shell prompt
*/

void display_prompt(void)
{
	if (isatty(STDIN_FILENO)) /* entrée standard (clav) interactif */
		write(STDOUT_FILENO, "#cisfun$ ", 9); /* écrit prompt ds sortie standard */
}
