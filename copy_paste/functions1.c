#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @types: List a of arguments
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars prnt.
 */
int print_unsigned(va_list types, char BFR[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = cnvrt_siz_unsnumber(num, size);

	if (num == 0)
		BFR[i--] = '0';

	BFR[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		BFR[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, BFR, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars prnt
 */
int print_octal(va_list types, char BFR[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = cnvrt_siz_unsnumber(num, size);

	if (num == 0)
		BFR[i--] = '0';

	BFR[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		BFR[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		BFR[i--] = '0';

	i++;

	return (write_unsgnd(0, i, BFR, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars prnt
 */
int print_hexadecimal(va_list types, char BFR[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", BFR,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars prnt
 */
int print_hexa_upper(va_list types, char BFR[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", BFR,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars prnt
 */
int print_hexa(va_list types, char map_to[], char BFR[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = cnvrt_siz_unsnumber(num, size);

	if (num == 0)
		BFR[i--] = '0';

	BFR[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		BFR[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		BFR[i--] = flag_ch;
		BFR[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, BFR, flags, width, precision, size));
}
