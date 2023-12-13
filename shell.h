#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/**
 * struct lists_s - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct lists_s
{
	int num;
	char *str;
	struct lists_s *next;
} llists_l;

/**
 * struct shell_infor - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @cmd_arg: a string of arguements generated from getline
 * @argv:an array of strings generated from cmd_arg
 * @path: a string path for the current command
 * @arg_count: the number of argument
 * @line_no: the error count
 * @err_code: the error code for the exit
 * @lineno_flag: if on count this line of input
 * @prog_name: the program filename
 * @env_ll: a linked list local copy of environ
 * @env_copy: custom modified copy of environ from linked lists env_ll
 * @history: a linked list of the commands' entered history for history node
 * @alias: a linked list for the alias node
 * @update_env: on if env_copy was altered
 * @status: the return status of the last executed command
 * @cmmd_buffer: address of pointer to cmmd_buffer, used in chaining
 * @cmmd_logic: command logical operators idx.e ||, &&, ;
 * @rd_fd: the file discriptor from which to read line input
 * @histo_no: the number of the entered commands
 */
typedef struct shell_infor
{
	char *cmd_arg;
	char **argv;
	char *path;
	int arg_count;
	unsigned int line_no;
	int err_code;
	int lineno_flag;
	char *prog_name;
	llists_l *env_ll;
	llists_l *history;
	llists_l *alias;
	char **env_copy;
	int update_env;
	int status;
	char **cmmd_buffer; /* ptr to cmd ; chain buffer, for mem mangement */
	int cmmd_logic; /* CMD_type ||, &&, ; */
	int rd_fd;
	int histo_no;
} sh_infor;

#define SH_INFOR_INITI \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}




#endif
