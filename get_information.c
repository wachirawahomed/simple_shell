#include "shell.h"

/**
 * clr_infor - initializes sh_infor struct
 * @data: struct address
 */
void clr_infor(sh_infor *data)
{
	data->cmd_arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->arg_count = 0;
}

/**
 * set_shinfor - initializes sh_infor struct
 * @data: struct address
 * @avec: argument vector
 */
void set_shinfor(sh_infor *data, char **avec)
{
	int idx = 0;

	data->prog_name = avec[0];
	if (data->cmd_arg)
	{
		data->argv = strg_tok(data->cmd_arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = str_duplic(data->cmd_arg);
				data->argv[1] = NULL;
			}
		}
		for (idx = 0; data->argv && data->argv[idx]; idx++)
			;
		data->arg_count = idx;

		update_alias(data);
		update_vars(data);
	}
}

/**
 * free_shinfor - frees sh_infor struct fields
 * @data: struct address
 * @a: true if freeing a fields
 */
void free_shinfor(sh_infor *data, int a)
{
	free_strg(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (a)
	{
		if (!data->cmmd_buffer)
			free(data->cmd_arg);
		if (data->env_ll)
			free_llist(&(data->env_ll));
		if (data->history)
			free_llist(&(data->history));
		if (data->alias)
			free_llist(&(data->alias));
		free_strg(data->env_copy);
		data->env_copy = NULL;
		free_mem((void **)data->cmmd_buffer);
		if (data->rd_fd > 2)
			close(data->rd_fd);
		_prtchar(BUFFER_FLUSH);
	}
}

