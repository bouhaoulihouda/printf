#include "main.h"

/****************** PRINTS THE VALUE OF A POINTER ******************/
/**
 * print_pointer - Prints the val of a ptr var
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_ch = 0, padd = ' ';
	int in = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_adrs;
	char map_to[] = "0123456789abcdef";
	void *adrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_adrs = (unsigned long)adrs;

	while (num_adrs > 0)
	{
		buffer[in--] = map_to[num_adrs % 16];
		num_adrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_ch = '+', length++;
	else if (flags & F_SPACE)
		extra_ch = ' ', length++;

	in++;

	/*return (write(1, &buffer[j], BUFF_SIZE - j - 1));*/
	return (write_pointer(buffer, in, length,
		width, flags, padd, extra_ch, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, offset = 0;
	char *strg = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strg == NULL)
		return (write(1, "(null)", 6));

	while (strg[j] != '\0')
	{
		if (is_printable(strg[j]))
			buffer[j + offset] = strg[j];
		else
			offset += append_hexa_code(strg[j], buffer, j + offset);

		j++;
	}

	buffer[j + offset] = '\0';

	return (write(1, buffer, j + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *strg;
	int j, cnt = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	strg = va_arg(types, char *);

	if (strg == NULL)
	{
		UNUSED(precision);

		strg = ")Null(";
	}
	for (j = 0; strg[j]; j++)
		;

	for (j = j - 1; j >= 0; j--)
	{
		char x = strg[j];

		write(1, &x, 1);
		cnt++;
	}
	return (cnt);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *strg;
	unsigned int j, k;
	int cnt = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	strg = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (strg == NULL)
		strg = "(AHYY)";
	for (j = 0; strg[j]; j++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == strg[j])
			{
				x = out[k];
				write(1, &x, 1);
				cnt++;
				break;
			}
		}
		if (!in[k])
		{
			x = strg[j];
			write(1, &x, 1);
			cnt++;
		}
	}
	return (cnt);
}
