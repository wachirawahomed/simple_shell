#include "shell.h"

/**
 * _getmyenviron - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **_getmyenviron(sh_infor *data)
{
	if (!data->env_copy || data->update_env)
	{
		data->env_copy = linkdlists_to_strg(data->env_ll);
		data->update_env = 0;
	}

	return (data->env_copy);
}

/**
 * _myenv_unset - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env_ll var property
 */
int _myenv_unset(sh_infor *data, char *var)
{
	llists_l *node = data->env_ll;
	size_t idx = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = str_search(node->str, var);
		if (q && *q == '=')
		{
			data->update_env = del_node_in_idx(&(data->env_ll), idx);
			idx = 0;
			node = data->env_ll;
			continue;
		}
		node = node->next;
		idx++;
	}
	return (data->update_env);
}

/**
 * init_shenv - Initialize a new environment variable,
 * or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env_ll var property
 * @val: the string env_ll var value
 * Return: Always 0
 */
int init_shenv(sh_infor *data, char *var, char *val)
{
	char *buff = NULL;
	llists_l *node;
	char *q;

	if (!var || !val)
		return (0);

	buff = malloc(str_lenght(var) + str_lenght(val) + 2);
	if (!buff)
		return (1);
	str_copy(buff, var);
	str_concat(buff, "=");
	str_concat(buff, val);
	node = data->env_ll;
	while (node)
	{
		q = str_search(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buff;
			data->update_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(data->env_ll), buff, 0);
	free(buff);
	data->update_env = 1;
	return (0);
}


