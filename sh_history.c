#include "shell.h"

/**
 * get_sh_history - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_sh_history(sh_infor *data)
{
	char *buff, *drc;

	drc = get_shenv(data, "HOME=");
	if (!drc)
		return (NULL);
	buff = malloc(sizeof(char) * (str_lenght(drc) +
				str_lenght(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_copy(buff, drc);
	str_concat(buff, "/");
	str_concat(buff, HISTORY_FILE);
	return (buff);
}

/**
 * wrt_history - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wrt_history(sh_infor *data)
{
	ssize_t fdes;
	char *f_name = get_sh_history(data);
	llists_l *node = NULL;

	if (!f_name)
		return (-1);

	fdes = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (fdes == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		prt_fd(node->str, fdes);
		wrt_fd('\n', fdes);
	}
	wrt_fd(BUFFER_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * rd_history - reads history from file
 * @data: the parameter struct
 *
 * Return: histo_no on success, 0 otherwise
 */
int rd_history(sh_infor *data)
{
	int idx, last = 0, l_count = 0;
	ssize_t fdes, read_len, f_sz = 0;
	struct stat srt;
	char *buff = NULL, *f_name = get_sh_history(data);

	if (!f_name)
		return (0);

	fdes = open(f_name, O_RDONLY);
	free(f_name);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &srt))
		f_sz = srt.st_size;
	if (f_sz < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_sz + 1));
	if (!buff)
		return (0);
	read_len = read(fdes, buff, f_sz);
	buff[f_sz] = 0;
	if (read_len <= 0)
		return (free(buff), 0);
	close(fdes);
	for (idx = 0; idx < f_sz; idx++)
		if (buff[idx] == '\n')
		{
			buff[idx] = 0;
			create_histo_lst(data, buff + last, l_count++);
			last = idx + 1;
		}
	if (last != idx)
		create_histo_lst(data, buff + last, l_count++);
	free(buff);
	data->histo_no = l_count;
	while (data->histo_no-- >= HISTORY_BUFFER_MAX)
		del_node_in_idx(&(data->history), 0);
	update_histo_no(data);
	return (data->histo_no);
}

/**
 * create_histo_lst - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @l_count: the history l_count, histo_no
 *
 * Return: Always 0
 */
int create_histo_lst(sh_infor *data, char *buff, int l_count)
{
	llists_l *node = NULL;

	if (data->history)
		node = data->history;
	add_end_node(&node, buff, l_count);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * update_histo_no - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histo_no
 */
int update_histo_no(sh_infor *data)
{
	llists_l *node = data->history;
	int idx = 0;

	while (node)
	{
		node->num = idx++;
		node = node->next;
	}
	return (data->histo_no = idx);
}
