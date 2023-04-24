#include "main.h"

void print_buffer(char buffer[], int *buff_in);

/**
 * _printf - Printf fct
 * @format: format.
 * Return: Printed characters.
 */
int _printf(const char *format, ...)
{
	int j, print = 0, printedChar = 0;
	int flags, width, precision, size, buff_in = 0;
	va_list lst;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lst, format);

	for (j = 0; format && format[j] != '\0'; j++)
	{
		if (format[j] != '%')
		{
			buffer[buff_in++] = format[j];
			if (buff_in == BUFF_SIZE)
				print_buffer(buffer, &buff_in);
			/* write(1, &format[j], 1);*/
			printedChar++;
		}
		else
		{
			print_buffer(buffer, &buff_in);
			flags = get_flags(format, &j);
			width = get_width(format, &j, lst);
			precision = get_precision(format, &j, lst);
			size = get_size(format, &j);
			++j;
			print = handle_print(format, &j, lst, buffer,
				flags, width, precision, size);
			if (print == -1)
				return (-1);
			printedChar += print;
		}
	}

	print_buffer(buffer, &buff_in);

	va_end(lst);

	return (printedChar);
}

/**
 * print_buffer - Prints the cntts of the buffer if it exist
 * @buffer: Array of characters
 * @buff_in: Indx at which to add next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_in)
{
	if (*buff_in > 0)
		write(1, &buffer[0], *buff_in);

	*buff_in = 0;
}
