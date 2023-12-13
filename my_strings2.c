#include "shell.h"

/**
 * *strgcopy - copies a string
 * @dst: the destination string to be copied to
 * @sre: the source string
 * @m: the amount of characters to be copied
 * Return: the concatenated string
 */
char *strgcopy(char *dst, char *sre, int m)
{
	int idx, q;
	char *r = dst;

	idx = 0;
	while (sre[idx] != '\0' && idx < m - 1)
	{
		dst[idx] = sre[idx];
		idx++;
	}
	if (idx < m)
	{
		q = idx;
		while (q < m)
		{
			dst[q] = '\0';
			q++;
		}
	}
	return (r);
}

/**
 * *strgconcat - concatenates two strings
 * @dst: the first string
 * @sre: the second string
 * @m: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *strgconcat(char *dst, char *sre, int m)
{
	int idx, q;
	char *r = dst;

	idx = 0;
	q = 0;
	while (dst[idx] != '\0')
		idx++;
	while (sre[q] != '\0' && q < m)
	{
		dst[idx] = sre[q];
		idx++;
		q++;
	}
	if (q < m)
		dst[idx] = '\0';
	return (r);
}

/**
 * *strgchar - locates a character in a string
 * @r: the string to be parsed
 * @cxt: the character to look for
 * Return: (r) a pointer to the memory area r
 */
char *strgchar(char *r, char cxt)
{
	do {
		if (*r == cxt)
			return (r);
	} while (*r++ != '\0');

	return (NULL);
}
