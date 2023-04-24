#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @ch: character types.
 * @buffer: Buffer arr to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Nbr of characters printed.
 */
int handle_write_char(char ch, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int j = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[j++] = ch;
	buffer[j] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (j = 0; j < width - 1; j++)
			buffer[BUFF_SIZE - j - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - j - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: List of args
 * @in: character types.
 * @buffer: Buffer arr to handle print
 * @flags:  Calcs active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Nbr of characters printed.
 */
int write_number(int is_negative, int in, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - in - 1;
	char pad = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(in, buffer, flags, width, precision,
		length, pad, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @in: Index at which the nbr starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Nbr length
 * @pad: Pading character
 * @extra_ch: Extra character
 *
 * Return: Nbr of printed characters.
 */
int write_num(int in, char buffer[],
	int flags, int width, int prec,
	int length, char pad, char extra_ch)
{
	int j, padd_start = 1;

	if (prec == 0 && in == BUFF_SIZE - 2 && buffer[in] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no character is printed */
	if (prec == 0 && in == BUFF_SIZE - 2 && buffer[in] == '0')
		buffer[in] = pad = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		pad = ' ';
	while (prec > length)
		buffer[--in] = '0', length++;
	if (extra_ch != 0)
		length++;
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
			buffer[j] = pad;
		buffer[j] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Asign extra chrctr to left of buffer */
		{
			if (extra_ch)
				buffer[--in] = extra_ch;
			return (write(1, &buffer[in], length) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra chrctr to left of buff */
		{
			if (extra_ch)
				buffer[--in] = extra_ch;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[in], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra chrctr to left of pad */
		{
			if (extra_ch)
				buffer[--padd_start] = extra_ch;
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[in], length - (1 - padd_start)));
		}
	}
	if (extra_ch)
		buffer[--in] = extra_ch;
	return (write(1, &buffer[in], length));
}

/**
 * write_unsgnd - Writes an unsigned nbr
 * @is_negative: Nbr indicating if the num is negative
 * @in: Index at which the nbr starts in the buffer
 * @buffer: Array of characters
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Nbr of written chars.
 */
int write_unsgnd(int is_negative, int in,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The nbr is str at the bufer's right and starts at position j */
	int length = BUFF_SIZE - in - 1, j = 0;
	char pad = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && in == BUFF_SIZE - 2 && buffer[in] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		pad = ' ';

	while (precision > length)
	{
		buffer[--in] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > length)
	{
		for (j = 0; j < width - length; j++)
			buffer[j] = pad;

		buffer[j] = '\0';

		if (flags & F_MINUS) /* Asign extra chrctr to left of buffer [buffer>pad]*/
		{
			return (write(1, &buffer[in], length) + write(1, &buffer[0], j));
		}
		else /* Asign extra character to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], j) + write(1, &buffer[in], length));
		}
	}

	return (write(1, &buffer[in], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrs of characters
 * @in: Idx at which the nbr starts in the buffer
 * @length: Length of nbr
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @pad: Character representing the padding
 * @extra_ch: Character representing extra character
 * @padd_start: Idx at which padding should start
 *
 * Return: Nbr of written chars.
 */
int write_pointer(char buffer[], int in, int length,
	int width, int flags, char pad, char extra_ch, int padd_start)
{
	int j;

	if (width > length)
	{
		for (j = 3; j < width - length + 3; j++)
			buffer[j] = pad;
		buffer[j] = '\0';
		if (flags & F_MINUS && pad == ' ')/* Asign extra chrctr to left of buffer */
		{
			buffer[--in] = 'x';
			buffer[--in] = '0';
			if (extra_ch)
				buffer[--in] = extra_ch;
			return (write(1, &buffer[in], length) + write(1, &buffer[3], j - 3));
		}
		else if (!(flags & F_MINUS) && pad == ' ')/* extra chrctr to left of bufr */
		{
			buffer[--in] = 'x';
			buffer[--in] = '0';
			if (extra_ch)
				buffer[--in] = extra_ch;
			return (write(1, &buffer[3], j - 3) + write(1, &buffer[in], length));
		}
		else if (!(flags & F_MINUS) && pad == '0')/* extra chrctr to left of pad */
		{
			if (extra_ch)
				buffer[--padd_start] = extra_ch;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[in], length - (1 - padd_start) - 2));
		}
	}
	buffer[--in] = 'x';
	buffer[--in] = '0';
	if (extra_ch)
		buffer[--in] = extra_ch;
	return (write(1, &buffer[in], BUFF_SIZE - in - 1));
}
