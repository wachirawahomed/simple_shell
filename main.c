#include "shell.h"

/**
 * main - entry point
 * @ac: arguement count
 * @avec: arguement vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **avec)
{
	sh_infor data[] = {SH_INFOR_INITI};
	int fdes = 2;

	fdes += 3;

	if (ac == 2)
	{
		fdes = open(avec[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eprt_str(avec[0]);
				eprt_str(": 0: Can't open ");
				eprt_str(avec[1]);
				eprt_char('\n');
				eprt_char(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->rd_fd = fdes;
	}
	fill_env_ll(data);
	rd_history(data);
	sh_loop(data, avec);
	return (EXIT_SUCCESS);
}
