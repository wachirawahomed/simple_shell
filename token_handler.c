#include "shell.h"

/**
 * **strg_tok - splits a string into words. Repeat delimiters are ignored
 * @strg: the input string
 * @delm: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strg_tok(char *strg, char *delm)
{
	int idx, q, w, e, no_words = 0;
	char **r;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (idx = 0; strg[idx] != '\0'; idx++)
		if (!delim_check(strg[idx], delm) &&
				(delim_check(strg[idx + 1], delm) ||
				 !strg[idx + 1]))
			no_words++;

	if (no_words == 0)
		return (NULL);
	r = malloc((1 + no_words) * sizeof(char *));
	if (!r)
		return (NULL);
	for (idx = 0, q = 0; q < no_words; q++)
	{
		while (delim_check(strg[idx], delm))
			idx++;
		w = 0;
		while (!delim_check(strg[idx + w], delm) && strg[idx + w])
			w++;
		r[q] = malloc((w + 1) * sizeof(char));
		if (!r[q])
		{
			for (w = 0; w < q; w++)
				free(r[w]);
			free(r);
			return (NULL);
		}
		for (e = 0; e < w; e++)
			r[q][e] = strg[idx++];
		r[q][e] = 0;
	}
	r[q] = NULL;
	return (r);
}

/**
 * **strg_tok_1 - splits a string into words
 * @strg: the input string
 * @delm: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strg_tok_1(char *strg, char delm)
{
	int idx, q, w, e, no_words = 0;
	char **r;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (idx = 0; strg[idx] != '\0'; idx++)
		if ((strg[idx] != delm && strg[idx + 1] == delm)
				|| strg[idx] != delm && !strg[idx + 1])
			|| strg[idx + 1] == delm)
			no_words++;
	if (no_words == 0)
		return (NULL);
	r = malloc((1 + no_words) * sizeof(char *));
	if (!r)
		return (NULL);
	for (idx = 0, q = 0; q < no_words; q++)
	{
		while (strg[idx] == delm && strg[idx] != delm)
			idx++;
		w = 0;
		while (strg[idx + w] != delm && strg[idx + w] &&
				strg[idx + w] != delm)
			w++;
		r[q] = malloc((w + 1) * sizeof(char));
		if (!r[q])
		{
			for (w = 0; w < q; w++)
				free(r[w]);
			free(r);
			return (NULL);
		}
		for (e = 0; e < w; e++)
			r[q][e] = strg[idx++];
		r[q][e] = 0;
	}
	r[q] = NULL;
	return (r);
}
