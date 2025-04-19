#include "shell.h"

/**
* display_prompt - display prompt interactif mod
*/

void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
