#include "shell.h"

/**
 * prt_currenv - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int prt_currenv(sh_infor *data)
{
	prt_list_strg(data->env_ll);
	return (0);
}

/**
 * get_shenv - gets the value of an environ variable
 * @data: Structure containing potential arguments. Used to maintain
 * @v_name: env_ll var name
 *
 * Return: the value
 */
char *get_shenv(sh_infor *data, const char *v_name)
{
	llists_l *node = data->env_ll;
	char *p;

	while (node)
	{
		p = str_search(node->str, v_name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_newenv - Initialize a new environment variable,
 * or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int set_newenv(sh_infor *data)
{
	if (data->arg_count != 3)
	{
		eprt_str("Incorrect number of arguements\n");
		return (1);
	}
	if (init_shenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_env - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int remove_env(sh_infor *data)
{
	int idx;

	if (data->arg_count == 1)
	{
		eprt_str("Too few arguements.\n");
		return (1);
	}
	for (idx = 1; idx <= data->arg_count; idx++)
		_myenv_unset(data, data->argv[idx]);

	return (0);
}

/**
 * fill_env_ll - populates env_ll linked list
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int fill_env_ll(sh_infor *data)
{
	llists_l *node = NULL;
	size_t idx;

	for (idx = 0; environ[idx]; idx++)
		add_end_node(&node, environ[idx], 0);
	data->env_ll = node;
	return (0);
}
