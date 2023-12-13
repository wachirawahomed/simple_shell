#include "shell.h"

/**
 * get_list_length - determines length of linked list
 * @f_nd: pointer to first node
 *
 * Return: size of list
 */
size_t get_list_length(const llists_l *f_nd)
{
	size_t idx = 0;

	while (f_nd)
	{
		f_nd = f_nd->next;
		idx++;
	}
	return (idx);
}

/**
 * linkdlists_to_strg - returns an array of strings of the list->str
 * @hd_add: pointer to first node
 *
 * Return: array of strings
 */
char **linkdlists_to_strg(llists_l *hd_add)
{
	llists_l *_nd = hd_add;
	size_t idx = get_list_length(hd_add), j;
	char **strs;
	char *str;

	if (!hd_add || !idx)
		return (NULL);
	strs = malloc(sizeof(char *) * (idx + 1));
	if (!strs)
		return (NULL);
	for (idx = 0; _nd; _nd = _nd->next, idx++)
	{
		str = malloc(str_lenght(_nd->str) + 1);
		if (!str)
		{
			for (j = 0; j < idx; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_copy(str, _nd->str);
		strs[idx] = str;
	}
	strs[idx] = NULL;
	return (strs);
}


/**
 * prt_llist_l - prints all elements of a llists_l linked list
 * @f_nd: pointer to first node
 *
 * Return: size of list
 */
size_t prt_llist_l(const llists_l *f_nd)
{
	size_t idx = 0;

	while (f_nd)
	{
		_prstr(convt_num(f_nd->num, 10, 0));
		_prtchar(':');
		_prtchar(' ');
		_prstr(f_nd->str ? f_nd->str : "(nil)");
		_prstr("\n");
		f_nd = f_nd->next;
		idx++;
	}
	return (idx);
}

/**
 * get_nd_with_prefix - returns node whose string starts with prefix
 * @_nd: pointer to list head
 * @pref: string to match
 * @c: the next character after prefix to match
 *
 * Return: match _nd or null
 */
llists_l *get_nd_with_prefix(llists_l *_nd, char *pref, char c)
{
	char *p = NULL;

	while (_nd)
	{
		p = str_search(_nd->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (_nd);
		_nd = _nd->next;
	}
	return (NULL);
}

/**
 * node_at_indx - gets the index of a node
 * @hd_add: pointer to list head
 * @_nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_at_indx(llists_l *hd_add, llists_l *_nd)
{
	size_t idx = 0;

	while (hd_add)
	{
		if (hd_add == _nd)
			return (idx);
		hd_add = hd_add->next;
		idx++;
	}
	return (-1);
}
