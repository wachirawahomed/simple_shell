#include "shell.h"

/**
 * test_if_delim - test if current char in buffer is a chain delimeter
 * @data: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int test_if_delim(sh_infor *data, char *buff, size_t *pos)
{
	size_t q = *pos;

	if (buff[q] == '|' && buff[q + 1] == '|')
	{
		buff[q] = 0;
		q++;
		data->cmmd_logic = COMMAND_OR;
	}
	else if (buff[q] == '&' && buff[q + 1] == '&')
	{
		buff[q] = 0;
		q++;
		data->cmmd_logic = COMMAND_AND;
	}
	else if (buff[q] == ';') /* found end of this command */
	{
		buff[q] = 0; /* replace semicolon with null */
		data->cmmd_logic = COMMAND_CHAIN;
	}
	else
		return (0);
	*pos = q;
	return (1);
}

/**
 * chk_chain - checks we should continue chaining based on last status
 * @data: the parameter struct
 * @buff: the char buffer
 * @pos: address of current position in buff
 * @idx: starting position in buff
 * @ln: length of buff
 *
 * Return: Void
 */
void chk_chain(sh_infor *data, char *buff, size_t *pos, size_t idx, size_t ln)
{
	size_t q = *pos;

	if (data->cmmd_logic == COMMAND_AND)
	{
		if (data->status)
		{
			buff[idx] = 0;
			q = ln;
		}
	}
	if (data->cmmd_logic == COMMAND_OR)
	{
		if (!data->status)
		{
			buff[idx] = 0;
			q = ln;
		}
	}

	*pos = q;
}

/**
 * update_alias - replaces an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int update_alias(sh_infor *data)
{
	int idx;
	llists_l *node;
	char *p;

	for (idx = 0; idx < 10; idx++)
	{
		node = get_nd_with_prefix(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = strgchar(node->str, '=');
		if (!p)
			return (0);
		p = str_duplic(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * update_vars - replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int update_vars(sh_infor *data)
{
	int idx = 0;
	llists_l *node;

	for (idx = 0; data->argv[idx]; idx++)
	{
		if (data->argv[idx][0] != '$' || !data->argv[idx][1])
			continue;

		if (!str_comp(data->argv[idx], "$?"))
		{
			update_string(&(data->argv[idx]), str_duplic
					(convt_num(data->status, 10, 0)));
			continue;
		}
		if (!str_comp(data->argv[idx], "$$"))
		{
			update_string(&(data->argv[idx]), str_duplic
					(convt_num(getpid(), 10, 0)));
			continue;
		}
		node = get_nd_with_prefix(data->env_ll, &data->argv[idx][1], '=');
		if (node)
		{
			update_string(&(data->argv[idx]),
					str_duplic(strgchar(node->str, '=') + 1));
			continue;
		}
		update_string(&data->argv[idx], str_duplic(""));

	}
	return (0);
}

/**
 * update_string - replaces string
 * @prev: address of prev string
 * @curr: curr string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int update_string(char **prev, char *curr)
{
	free(*prev);
	*prev = curr;
	return (1);
}
