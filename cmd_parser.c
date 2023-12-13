#include "shell.h"
/**
 * is_exctbl - determines if a file is an executable command
 * @data: the data struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_exctbl(sh_infor *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * cha_dupli - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *cha_dupli(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int idx = 0, k = 0;

	for (k = 0, idx = start; idx < stop; idx++)
		if (pathstr[idx] != ':')
			buf[k++] = pathstr[idx];
	buf[k] = 0;
	return (buf);
}

/**
 * get_path - finds this cmd in the PATH string
 * @data: the data struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(sh_infor *data, char *pathstr, char *cmd)
{
	int idx = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_lenght(cmd) > 2) && str_search(cmd, "./"))
	{
		if (is_exctbl(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[idx] || pathstr[idx] == ':')
		{
			path = cha_dupli(pathstr, curr_pos, idx);
			if (!*path)
				str_concat(path, cmd);
			else
			{
				str_concat(path, "/");
				str_concat(path, cmd);
			}
			if (is_exctbl(data, path))
				return (path);
			if (!pathstr[idx])
				break;
			curr_pos = idx;
		}
		idx++;
	}
	return (NULL);
}
