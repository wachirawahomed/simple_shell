#include "shell.h"

/**
 * add_start_node - adds a node to the start of the list
 * @hd_add: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
llists_l *add_start_node(llists_l **hd_add, const char *str, int num)
{
	llists_l *new_hd;

	if (!hd_add)
		return (NULL);
	new_hd = malloc(sizeof(llists_l));
	if (!new_hd)
		return (NULL);
	set_mem((void *)new_hd, 0, sizeof(llists_l));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = str_duplic(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd_add;
	*hd_add = new_hd;
	return (new_hd);
}

/**
 * add_end_node - adds a node to the end of the list
 * @hd_add: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
llists_l *add_end_node(llists_l **hd_add, const char *str, int num)
{
	llists_l *new_nd, *_nd;

	if (!hd_add)
		return (NULL);

	_nd = *hd_add;
	new_nd = malloc(sizeof(llists_l));
	if (!new_nd)
		return (NULL);
	set_mem((void *)new_nd, 0, sizeof(llists_l));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = str_duplic(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (_nd)
	{
		while (_nd->next)
			_nd = _nd->next;
		_nd->next = new_nd;
	}
	else
		*hd_add = new_nd;
	return (new_nd);
}

/**
 * prt_list_strg - prints only the str element of a llists_l linked list
 * @f_nd: pointer to first node
 *
 * Return: size of list
 */
size_t prt_list_strg(const llists_l *f_nd)
{
	size_t idx = 0;

	while (f_nd)
	{
		_prstr(f_nd->str ? f_nd->str : "(nil)");
		_prstr("\n");
		f_nd = f_nd->next;
		idx++;
	}
	return (idx);
}

/**
 * del_node_in_idx - deletes node at given index
 * @hd_add: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_in_idx(llists_l **hd_add, unsigned int index)
{
	llists_l *_nd, *prev_nd;
	unsigned int idx = 0;

	if (!hd_add || !*hd_add)
		return (0);

	if (!index)
	{
		_nd = *hd_add;
		*hd_add = (*hd_add)->next;
		free(_nd->str);
		free(_nd);
		return (1);
	}
	_nd = *hd_add;
	while (_nd)
	{
		if (idx == index)
		{
			prev_nd->next = _nd->next;
			free(_nd->str);
			free(_nd);
			return (1);
		}
		idx++;
		prev_nd = _nd;
		_nd = _nd->next;
	}
	return (0);
}

/**
 * free_llist - frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_llist(llists_l **hd_ptr)
{
	llists_l *_nd, *nxt_nd, *hd_add;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd_add = *hd_ptr;
	_nd = hd_add;
	while (_nd)
	{
		nxt_nd = _nd->next;
		free(_nd->str);
		free(_nd);
		_nd = nxt_nd;
	}
	*hd_ptr = NULL;
}

