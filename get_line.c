#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @data: parameter struct
 * @buff: address of buffer
 * @dln: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(sh_infor *data, char **buff, size_t *dln)
{
	ssize_t rs = 0;
	size_t len_p = 0;

	if (!*dln) /* if nothing left in the buffer, fill it */
	{
		/*free_mem((void **)data->cmmd_buffer);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, handle_signint);
#if USE_GETLINE
		rs = getline(buff, &len_p, stdin);
#else
		rs = myget_line(data, buff, &len_p);
#endif
		if (rs > 0)
		{
			if ((*buff)[rs - 1] == '\n')
			{
				(*buff)[rs - 1] = '\0'; /* remove trailing newline */
				rs--;
			}
			data->lineno_flag = 1;
			remove_cmmt(*buff);
			create_histo_lst(data, *buff, data->histo_no++);
			/* if (strgchar(*buff, ';')) is this a command chain? */
			{
				*dln = rs;
				data->cmmd_buffer = buff;
			}
		}
	}
	return (rs);
}

/**
 * get_uxinput - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_uxinput(sh_infor *data)
{
	static char *buff; /* the ';' command chain buffer */
	static size_t idx, q, lgt;
	ssize_t rs = 0;
	char **buf_p = &(data->cmd_arg), *p;

	_prtchar(BUFFER_FLUSH);
	rs = input_buffer(data, &buff, &lgt);
	if (rs == -1) /* EOF */
		return (-1);
	if (lgt) /* we have commands left in the chain buffer */
	{
		q = idx; /* init new iterator to current buff position */
		p = buff + idx; /* get pointer for return */

		chk_chain(data, buff, &q, idx, lgt);
		while (q < lgt) /* iterate to semicolon or end */
		{
			if (test_if_delim(data, buff, &q))
				break;
			q++;
		}

		idx = q + 1; /* increment past nulled ';'' */
		if (idx >= lgt) /* reached end of buffer? */
		{
			idx = lgt = 0; /* reset position and length */
			data->cmmd_logic = COMMAD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (str_lenght(p)); /* return length of current command */
	}

	*buf_p = buff; /* else not a chain, pass back buffer from myget_line() */
	return (rs); /* return length of buffer from myget_line() */
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buff: buffer
 * @idx: size
 *
 * Return: rs
 */
ssize_t read_buf(sh_infor *data, char *buff, size_t *idx)
{
	ssize_t rs = 0;

	if (*idx)
		return (0);
	rs = read(data->rd_fd, buff, READ_BUFFER);
	if (rs >= 0)
		*idx = rs;
	return (rs);
}

/**
 * myget_line - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: r
 */
int myget_line(sh_infor *data, char **ptr, size_t *length)
{
	static char buff[READ_BUFFER];
	static size_t idx, lgt;
	size_t w;
	ssize_t rs = 0, r = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		r = *length;
	if (idx == lgt)
		idx = lgt = 0;

	rs = read_buf(data, buff, &lgt);
	if (rs == -1 || (rs == 0 && lgt == 0))
		return (-1);

	c = strgchar(buff + idx, '\n');
	w = c ? 1 + (unsigned int)(c - buff) : lgt;
	new_p = mem_realoc(p, r, r ? r + w : w + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (r)
		strgconcat(new_p, buff + idx, w - idx);
	else
		strgcopy(new_p, buff + idx, w - idx + 1);

	r += w - idx;
	idx = w;
	p = new_p;

	if (length)
		*length = r;
	*ptr = p;
	return (r);
}

/**
 * handle_signint - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_signint(__attribute__((unused))int sig_num)
{
	_prstr("\n");
	_prstr("$ ");
	_prtchar(BUFFER_FLUSH);
}
