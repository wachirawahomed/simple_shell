#include "shell.h"
/**
 * str_copy - copies a string
 * @dst: the destination
 * @sre: the source
 *
 * Return: pointer to destination
 */
char *str_copy(char *dst, char *sre)
{
	int idx = 0;

	if (dst == sre || sre == 0)
		return (dst);
	while (sre[idx])
	{
		dst[idx] = sre[idx];
		idx++;
	}
	dst[idx] = 0;
	return (dst);
}

/**
 * str_duplic - duplicates a string
 * @strg: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_duplic(const char *strg)
{
	int len = 0;
	char *rtrn;

	if (strg == NULL)
		return (NULL);
	while (*strg++)
		len++;
	rtrn = malloc(sizeof(char) * (len + 1));
	if (!rtrn)
		return (NULL);
	for (len++; len--;)
		rtrn[len] = *--strg;
	return (rtrn);
}

/**
 * _prstr - prints an input string
 * @strg: the string to be printed
 *
 * Return: Nothing
 */
void _prstr(char *strg)
{
	int idx = 0;

	if (!strg)
		return;
	while (strg[idx] != '\0')
	{
		_prtchar(strg[idx]);
		idx++;
	}
}

/**
 * _prtchar - writes the character c to stdout
 * @cxt: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _prtchar(char cxt)
{
	static int idx;
	static char buff[WRITE_BUFFER];

	if (cxt == BUFFER_FLUSH || idx >= WRITE_BUFFER)
	{
		write(1, buff, idx);
		idx = 0;
	}
	if (cxt != BUFFER_FLUSH)
		buff[idx++] = cxt;
	return (1);
}
