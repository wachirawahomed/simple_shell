#include "shell.h"

/**
 * prt_error - prints an error message
 * @data: the parameter & return data struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void prt_error(sh_infor *data, char *estr)
{
	eprt_str(data->prog_name);
	eprt_str(": ");
	prt_deci(data->line_no, STDERR_FILENO);
	eprt_str(": ");
	eprt_str(data->argv[0]);
	eprt_str(": ");
	eprt_str(estr);
}

/**
 * prt_deci - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fdes: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prt_deci(int input, int fdes)
{
	int (*__putchar)(char) = _prtchar;
	int idx, cnt = 0;
	unsigned int _ab, crrt;

	if (fdes == STDERR_FILENO)
		__putchar = eprt_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_ab = input;
	crrt = _ab;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (_ab / idx)
		{
			__putchar('0' + crrt / idx);
			cnt++;
		}
		crrt %= idx;
	}
	__putchar('0' + crrt);
	cnt++;

	return (cnt);
}

/**
 * convt_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convt_num(long int num, int base, int flags)
{
	static char *arry;
	static char bffr[50];
	char s = 0;
	char *p;
	unsigned long no = num;

	if (!(flags & UNSIGNED_CONV) && num < 0)
	{
		no = -num;
		s = '-';

	}
	arry = flags & LOWERCASE_CONV ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &bffr[49];
	*p = '\0';

	do	{
		*--p = arry[no % base];
		no /= base;
	} while (no != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * remove_cmmt - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_cmmt(char *buff)
{
	int idx;

	for (idx = 0; buff[idx] != '\0'; idx++)
		if (buff[idx] == '#' && (!idx || buff[idx - 1] == ' '))
		{
			buff[idx] = '\0';
			break;
		}
}

