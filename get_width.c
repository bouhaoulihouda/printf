#include "main.h"

/**
 * get_width - Calcs the width for printing
 * @format: Formatted strg in which to print the args.
 * @j: List of args to be printed.
 * @list: list of args.
 *
 * Return: width.
 */
int get_width(const char *format, int *j, va_list list)
{
	int curr_j;
	int width = 0;

	for (curr_j = *j + 1; format[curr_j] != '\0'; curr_j++)
	{
		if (is_digit(format[curr_j]))
		{
			width *= 10;
			width += format[curr_j] - '0';
		}
		else if (format[curr_j] == '*')
		{
			curr_j++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*j = curr_j - 1;

	return (width);
}
