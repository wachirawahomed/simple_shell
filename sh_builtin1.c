#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @data: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(sh_infor *data, char *strg)
{
	char *r, cx;
	int rtn;

	r = strgchar(strg, '=');
	if (!r)
		return (1);
	cx = *r;
	*r = 0;
	rtn = del_node_in_idx(&(data->alias),
			node_at_indx(data->alias,
				get_nd_with_prefix(data->alias, strg, -1)));
	*r = cx;
	return (rtn);
}

/**
 * set_alias - sets alias to string
 * @data: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(sh_infor *data, char *strg)
{
	char *r;

	r = strgchar(strg, '=');
	if (!r)
		return (1);
	if (!*++r)
		return (unset_alias(data, strg));

	unset_alias(data, strg);
	return (add_end_node(&(data->alias), strg, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(llists_l *node)
{
	char *r = NULL, *s = NULL;

	if (node)
	{
		r = strgchar(node->str, '=');
		for (s = node->str; s <= r; s++)
			_prtchar(*s);
		_prtchar('\'');
		_prstr(r + 1);
		_prstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_mycmd - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int alias_mycmd(sh_infor *data)
{
	int idx = 0;
	char *r = NULL;
	llists_l *node = NULL;

	if (data->arg_count == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (idx = 1; data->argv[idx]; idx++)
	{
		r = strgchar(data->argv[idx], '=');
		if (r)
			set_alias(data, data->argv[idx]);
		else
			print_alias(get_nd_with_prefix(data->alias,
						data->argv[idx], '='));
	}

	return (0);
}
