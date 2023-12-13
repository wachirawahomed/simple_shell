#include "shell.h"

/**
 * eprt_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void eprt_str(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		eprt_char(str[idx]);
		idx++;
	}
}

/**
 * eprt_char - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int eprt_char(char c)
{
	static int idx;
	static char buff[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || idx >= WRITE_BUFFER)
	{
		write(2, buff, idx);
		idx = 0;
	}
	if (c != BUFFER_FLUSH)
		buff[idx++] = c;
	return (1);
}

/**
 * err_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int err_atoi(char *s)
{
	int idx = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (idx = 0;  s[idx] != '\0'; idx++)
	{
		if (s[idx] >= '0' && s[idx] <= '9')
		{
			result *= 10;
			result += (s[idx] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * wrt_fd - writes the character c to given fdes
 * @c: The character to print
 * @fdes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wrt_fd(char c, int fdes)
{
	static int idx;
	static char buff[WRITE_BUFFER];

	if (c == BUFFER_FLUSH || idx >= WRITE_BUFFER)
	{
		write(fdes, buff, idx);
		idx = 0;
	}
	if (c != BUFFER_FLUSH)
		buff[idx++] = c;
	return (1);
}

/**
 * prt_fd - prints an input string
 * @str: the string to be printed
 * @fdes: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int prt_fd(char *str, int fdes)
{
	int idx = 0;

	if (!str)
		return (0);
	while (*str)
	{
		idx += wrt_fd(*str++, fdes);
	}
	return (idx);
}
