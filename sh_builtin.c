#include "shell.h"

/**
 * exit_cmd - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if data.argv[0] != "exit"
 */
int exit_cmd(sh_infor *data)
{
	int exit_chk;

	if (data->argv[1]) /* If there is an exit arguement */
	{
		exit_chk = err_atoi(data->argv[1]);
		if (exit_chk == -1)
		{
			data->status = 2;
			prt_error(data, "Illegal number: ");
			eprt_str(data->argv[1]);
			eprt_char('\n');
			return (1);
		}
		data->err_code = err_atoi(data->argv[1]);
		return (-2);
	}
	data->err_code = -1;
	return (-2);
}

/**
 * cd_cmd - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int cd_cmd(sh_infor *data)
{
	char *r, *dir, buffer[1024];
	int __chdir;

	r = getcwd(buffer, 1024);
	if (!r)
		_prstr("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = get_shenv(data, "HOME=");
		if (!dir)
			__chdir = /* TODO: what should this be? */
				chdir((dir = get_shenv(data, "PWD=")) ? dir : "/");
		else
			__chdir = chdir(dir);
	}
	else if (str_comp(data->argv[1], "-") == 0)
	{
		if (!get_shenv(data, "OLDPWD="))
		{
			_prstr(r);
			_prtchar('\n');
			return (1);
		}
		_prstr(get_shenv(data, "OLDPWD=")), _prtchar('\n');
		__chdir = /* TODO: what should this be? */
			chdir((dir = get_shenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		__chdir = chdir(data->argv[1]);
	if (__chdir == -1)
	{
		prt_error(data, "can't cd to ");
		eprt_str(data->argv[1]), eprt_char('\n');
	}
	else
	{
		init_shenv(data, "OLDPWD", get_shenv(data, "PWD="));
		init_shenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_cmd - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int help_cmd(sh_infor *data)
{
	char **arg_array;

	arg_array = data->argv;
	_prstr("help call works. Function not yet implemented \n");
	if (0)
		_prstr(*arg_array); /* temp att_unused workaround */
	return (0);
}


/**
 * sh_history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int sh_history(sh_infor *data)
{
	prt_llist_l(data->history);
	return (0);
}
