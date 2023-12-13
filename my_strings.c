#include "shell.h"

/**
 * str_lenght - returns the length of a string
 * @r: the string whose length to check
 *
 * Return: integer length of string
 */
int str_lenght(char *r)
{
	int idx = 0;

	if (!r)
		return (0);

	while (*r++)
		idx++;
	return (idx);
}

/**
 * str_comp - performs lexicogarphic comparison of two strangs.
 * @s_1: the first strang
 * @s_2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_comp(char *s_1, char *s_2)
{
	while (*s_1 && *s_2)
	{
		if (*s_1 != *s_2)
			return (*s_1 - *s_2);
		s_1++;
		s_2++;
	}
	if (*s_1 == *s_2)
		return (0);
	else
		return (*s_1 < *s_2 ? -1 : 1);
}

/**
 * str_search - checks if needle starts with haystack
 * @stack: string to search
 * @sub_str: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *str_search(const char *stack, const char *sub_str)
{
	while (*sub_str)
		if (*sub_str++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * str_concat - concatenates two strings
 * @dst: the destination buffer
 * @sre: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_concat(char *dst, char *sre)
{
	char *rtrn = dst;

	while (*dst)
		dst++;
	while (*sre)
		*dst++ = *sre++;
	*dst = *sre;
	return (rtrn);
}
