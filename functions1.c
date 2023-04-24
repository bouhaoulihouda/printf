#include "main.h"

/************************* PRINTS AN UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned nbr
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[j--] = (numb % 10) + '0';
		numb /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_num = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[j--] = (numb % 8) + '0';
		numb /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/************** PRINTS AN UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned nb in hexadecimal notation
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'y', width, precision, size));
}

/************* PRINTS AN UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List a of args
 * @buffer: Buffer array to handle print
 * @flags:  Calcs active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Nbr of characters printed.
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'Y', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal nbr in upper or lower
 * @types: Lista of arguments
 * @map_to: Arr of vls to map the nbr to
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs the active flags
 * @flag_ch: Calcs the active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Nbr of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int numb = va_arg(types, unsigned long int);
	unsigned long int init_num = numb;

	UNUSED(width);

	numb = convert_size_unsgnd(numb, size);

	if (numb == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numb > 0)
	{
		buffer[j--] = map_to[numb % 16];
		numb /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}
