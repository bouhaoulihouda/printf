#include "main.h"

/**
 * is_printable - Evaluates if a character is printable
 * @ch: Char to be evaluated.
 *
 * Return: 1 if ch is printable, 0 otherwise
 */
int is_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @j: Ind at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int j)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[j++] = '\\';
	buffer[j++] = 'x';

	buffer[j++] = map_to[ascii_code / 16];
	buffer[j] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @ch: Character to be evaluated
 *
 * Return: 1 if ch is a digit, 0 otherwise
 */
int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a nbr to the specified size
 * @numb: Nbr to be casted.
 * @size: Nbr indicating the type to be casted.
 *
 * Return: Casted val of num
 */
long int convert_size_number(long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((short)numb);

	return ((int)numb);
}

/**
 * convert_size_unsgnd - Casts a nbr to the specified size
 * @numb: Nbr to be casted
 * @size: Nbr indicating the type to be casted
 *
 * Return: Casted val of num
 */
long int convert_size_unsgnd(unsigned long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((unsigned short)numb);

	return ((unsigned int)numb);
}
