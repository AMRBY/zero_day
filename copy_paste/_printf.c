#include "main.h"

void print_BFR(char BFR[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, prnt = 0, prnt_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char BFR[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			BFR[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_BFR(BFR, &buff_ind);
			/* write(1, &format[i], 1);*/
			prnt_chars++;
		}
		else
		{
			print_BFR(BFR, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			prnt = handle_print(format, &i, list, BFR,
				flags, width, precision, size);
			if (prnt == -1)
				return (-1);
			prnt_chars += prnt;
		}
	}

	print_BFR(BFR, &buff_ind);

	va_end(list);

	return (prnt_chars);
}

/**
 * print_BFR - Prints the contents of the BFR if it exist
 * @BFR: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_BFR(char BFR[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &BFR[0], *buff_ind);

	*buff_ind = 0;
}
