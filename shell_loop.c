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
