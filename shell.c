#include "main.h"
/**
 * main - the entry point of the shell
 *
 * @ac: the number of arguments
 * @av: the arguments
 *
 * Return: alway 0.
 */

int main(int ac, char **av)
{
	char *prompt = "$ ";
	char *lineptr;
	size_t n = 0;

	(void)ac; (void)av;
	while (1)
	{
		printf("%s", prompt);
		getline(&lineptr, &n, stdin);
	}

	free(lineptr);
	return (0);
}
