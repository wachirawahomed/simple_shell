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

/* shell_loop.c */
int sh_loop(sh_infor *, char **);
int get_builtin(sh_infor *);
void get_cmd(sh_infor *);
void _fork(sh_infor *);

/* cmd_parser.c */
int is_exctbl(sh_infor *, char *);
char *cha_dupli(char *, int, int);
char *get_path(sh_infor *, char *, char *);

/* error_handle.c */
void eprt_str(char *);
int eprt_char(char);
int wrt_fd(char c, int fdes);
int prt_fd(char *str, int fdes);
int err_atoi(char *);

/* error_handle1.c */
int prt_deci(int, int);
char *convt_num(long int, int, int);
void prt_error(sh_infor *, char *);
void remove_cmmt(char *);

/* llist_handler.c */
llists_l *add_start_node(llists_l **, const char *, int);
llists_l *add_end_node(llists_l **, const char *, int);
size_t prt_list_strg(const llists_l *);
int del_node_in_idx(llists_l **, unsigned int);
void free_llist(llists_l **);

/* llist_handler1.c */
size_t get_list_length(const llists_l *);
char **linkdlists_to_strg(llists_l *);
size_t prt_llist_l(const llists_l *);
llists_l *get_nd_with_prefix(llists_l *, char *, char);
ssize_t node_at_indx(llists_l *, llists_l *);

/* token_handler.c */
char **strg_tok(char *, char *);
char **strg_tok_1(char *, char);

/* token_handler.c */
char **strg_tok(char *, char *);
char **strg_tok_1(char *, char);

/* memory_handler.c */
char *set_mem(char *, char, unsigned int);
void free_strg(char **);
void *mem_realoc(void *, unsigned int, unsigned int);
int free_mem(void **);

/* my_strings.c */
int str_lenght(char *);
int str_comp(char *, char *);
char *str_search(const char *, const char *);
char *str_concat(char *, char *);

/* my_strings1.c */
char *str_copy(char *, char *);
char *str_duplic(const char *);
void _prstr(char *);
int _prtchar(char);

/* my_strings2.c */
char *strgcopy(char *, char *, int);
char *strgconcat(char *, char *, int);
char *strgchar(char *, char);


#endif
