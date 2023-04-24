#include "main.h"

/************************* PRINT A CHARACTER *************************/

/**
 * print_char - Prints a character
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs the active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size spefr
 * Return: Nb of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}
/************************* PRINT A STR *************************/
/**
 * print_string - Prints a str
 * @types: List a of args
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nb of chararacters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *strg = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (strg == NULL)
	{
		strg = "(null)";
		if (precision >= 6)
			strg = "      ";
	}

	while (strg[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &strg[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &strg[0], length);
			return (width);
		}
	}

	return (write(1, strg, length));
}
/************************* PRINTS A PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: List of args
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs the active flags
 * @width: get the width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Prints an integer
 * @types: Liste of args
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs the active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int isNegative = 0;
	long int m = va_arg(types, long int);
	unsigned long int numb;

	m = convert_size_number(m, size);

	if (m == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)m;

	if (m < 0)
	{
		numb = (unsigned long int)((-1) * m);
		isNegative = 1;
	}

	while (numb > 0)
	{
		buffer[j--] = (numb % 10) + '0';
		numb /= 10;
	}

	j++;

	return (write_number(isNegative, j, buffer, flags, width, precision, size));
}

/************************* PRINT A BINARY *************************/
/**
 * print_binary - Prints an unsigned nbr
 *@types: Liste of args
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs the active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, j, sum;
	unsigned int b[32];
	int cnt;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ^ 31) */
	b[0] = x / y;
	for (j = 1; j < 32; j++)
	{
		y /= 2;
		b[j] = (x / y) % 2;
	}
	for (j = 0, sum = 0, cnt = 0; j < 32; j++)
	{
		sum += b[j];
		if (sum || j == 31)
		{
			char y = '0' + b[j];

			write(1, &y, 1);
			cnt++;
		}
	}
	return (cnt);
}
