#include "shell.h"

/**
 * set_mem - fills memory with a constant byte
 * @r: the pointer to the memory area
 * @bt: the byte to fill *r with
 * @u: the amount of bytes to be filled
 * Return: (r) a pointer to the memory area r
 */
char *set_mem(char *r, char bt, unsigned int u)
{
	unsigned int idx;

	for (idx = 0; idx < u; idx++)
		r[idx] = bt;
	return (r);
}

/**
 * free_strg - frees a string of strings
 * @p_str: string of strings
 */
void free_strg(char **p_str)
{
	char **x = p_str;

	if (!p_str)
		return;
	while (*p_str)
		free(*p_str++);
	free(x);
}

/**
 * mem_realoc - reallocates a block of memory
 * @pxt: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @set_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *mem_realoc(void *pxt, unsigned int prev_size, unsigned int set_size)
{
	char *s;

	if (!pxt)
		return (malloc(set_size));
	if (!set_size)
		return (free(pxt), NULL);
	if (set_size == prev_size)
		return (pxt);

	s = malloc(set_size);
	if (!s)
		return (NULL);

	prev_size = prev_size < set_size ? prev_size : set_size;
	while (prev_size--)
		s[prev_size] = ((char *)pxt)[prev_size];
	free(pxt);
	return (s);
}

/**
 * free_mem - frees a pointer and NULLs the address
 * @pxt: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_mem(void **pxt)
{
	if (pxt && *pxt)
	{
		free(*pxt);
		*pxt = NULL;
		return (1);
	}
	return (0);
}
