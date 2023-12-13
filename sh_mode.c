#include "shell.h"

/**
 * intera_mode - returns true if shell is intera_mode mode
 * @data: struct address
 *
 * Return: 1 if intera_mode mode, 0 otherwise
 */
int intera_mode(sh_infor *data)
{
	return (isatty(STDIN_FILENO) && data->rd_fd <= 2);
}

/**
 * delim_check - checks if character is a delimeter
 * @cxt: the char to check
 * @dlim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delim_check(char cxt, char *dlim)
{
	while (*dlim)
		if (*dlim++ == cxt)
			return (1);
	return (0);
}

/**
 * check_alpha - checks for alphabetic character
 * @cxt: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int check_alpha(int cxt)
{
	if ((cxt >= 'a' && cxt <= 'z') || (cxt >= 'A' && cxt <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_int - converts a string to an integer
 * @r: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int str_int(char *r)
{
	int idx, sgn = 1, fg = 0, o_put;
	unsigned int res = 0;

	for (idx = 0; r[idx] != '\0' && fg != 2; idx++)
	{
		if (r[idx] == '-')
			sgn *= -1;

		if (r[idx] >= '0' && r[idx] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (r[idx] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sgn == -1)
		o_put = -res;
	else
		o_put = res;

	return (o_put);
}
