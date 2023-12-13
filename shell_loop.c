#include "shell.h"

/**
 * sh_loop - the shell loop
 * @data: the parameter & return data struct
 * @avec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sh_loop(sh_infor *data, char **avec)
{
	ssize_t rs = 0;
	int bltin_return = 0;

	while (rs != -1 && bltin_return != -2)
	{
		clr_infor(data);
		if (intera_mode(data))
			_prstr("$ ");
		eprt_char(BUFFER_FLUSH);
		rs = get_uxinput(data);
		if (rs != -1)
		{
			set_shinfor(data, avec);
			bltin_return = get_builtin(data);
			if (bltin_return == -1)
				get_cmd(data);
		}
		else if (intera_mode(data))
			_prtchar('\n');
		free_shinfor(data, 0);
	}
	wrt_history(data);
	free_shinfor(data, 1);
	if (!intera_mode(data) && data->status)
		exit(data->status);
	if (bltin_return == -2)
	{
		if (data->err_code == -1)
			exit(data->status);
		exit(data->err_code);
	}
	return (bltin_return);
}

/**
 * get_builtin - finds a builtin command
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int get_builtin(sh_infor *data)
{
	int idx, bltin_return = -1;
	builtin_cmd_tbl builtintbl[] = {
		{"exit", exit_cmd},
		{"env", prt_currenv},
		{"help", help_cmd},
		{"history", sh_history},
		{"setenv", set_newenv},
		{"unsetenv", remove_env},
		{"cd", cd_cmd},
		{"alias", alias_mycmd},
		{NULL, NULL}
	};

	for (idx = 0; builtintbl[idx].type; idx++)
		if (str_comp(data->argv[0], builtintbl[idx].type) == 0)
		{
			data->line_no++;
			bltin_return = builtintbl[idx].func(data);
			break;
		}
	return (bltin_return);
}

/**
 * get_cmd - finds a command in PATH
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void get_cmd(sh_infor *data)
{
	char *path = NULL;
	int idx, k;

	data->path = data->argv[0];
	if (data->lineno_flag == 1)
	{
		data->line_no++;
		data->lineno_flag = 0;
	}
	for (idx = 0, k = 0; data->cmd_arg[idx]; idx++)
		if (!delim_check(data->cmd_arg[idx], " \t\n"))
			k++;
	if (!k)
		return;

	path = get_path(data, get_shenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		_fork(data);
	}
	else
	{
		if ((intera_mode(data) || get_shenv(data, "PATH=")
					|| data->argv[0][0] == '/')
				&& is_cmd(data, data->argv[0]))
			_fork(data);
		else if (*(data->cmd_arg) != '\n')
		{
			data->status = 127;
			prt_error(data, "not found\n");
		}
	}
}

/**
 * _fork - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 *
 * Return: void
 */
void _fork(sh_infor *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, _getmyenviron(data)) == -1)
		{
			free_shinfor(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				prt_error(data, "Permission denied\n");
		}
	}
}
