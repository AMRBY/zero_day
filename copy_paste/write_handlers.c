#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars prnt.
 */
int handle_write_char(char c, char BFR[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at BFR's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	BFR[i++] = c;
	BFR[i] = '\0';

	if (width > 1)
	{
		BFR[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			BFR[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &BFR[0], 1) +
					write(1, &BFR[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &BFR[BUFF_SIZE - i - 1], width - 1) +
					write(1, &BFR[0], 1));
	}

	return (write(1, &BFR[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @BFR: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars prnt.
 */
int write_number(int is_negative, int ind, char BFR[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, BFR, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the BFR
 * @BFR: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of prnt chars.
 */
int write_num(int ind, char BFR[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && BFR[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is prnt */
	if (prec == 0 && ind == BUFF_SIZE - 2 && BFR[ind] == '0')
		BFR[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		BFR[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			BFR[i] = padd;
		BFR[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of BFR */
		{
			if (extra_c)
				BFR[--ind] = extra_c;
			return (write(1, &BFR[ind], length) + write(1, &BFR[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				BFR[--ind] = extra_c;
			return (write(1, &BFR[1], i - 1) + write(1, &BFR[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				BFR[--padd_start] = extra_c;
			return (write(1, &BFR[padd_start], i - padd_start) +
				write(1, &BFR[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		BFR[--ind] = extra_c;
	return (write(1, &BFR[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the BFR
 * @BFR: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char BFR[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && BFR[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is prnt */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		BFR[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			BFR[i] = padd;

		BFR[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of BFR [BFR>padd]*/
		{
			return (write(1, &BFR[ind], length) + write(1, &BFR[0], i));
		}
		else /* Asign extra char to left of padding [padd>BFR]*/
		{
			return (write(1, &BFR[0], i) + write(1, &BFR[ind], length));
		}
	}

	return (write(1, &BFR[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @BFR: Arrays of chars
 * @ind: Index at which the number starts in the BFR
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char BFR[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			BFR[i] = padd;
		BFR[i] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of BFR */
		{
			BFR[--ind] = 'x';
			BFR[--ind] = '0';
			if (extra_c)
				BFR[--ind] = extra_c;
			return (write(1, &BFR[ind], length) + write(1, &BFR[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of BFR */
		{
			BFR[--ind] = 'x';
			BFR[--ind] = '0';
			if (extra_c)
				BFR[--ind] = extra_c;
			return (write(1, &BFR[3], i - 3) + write(1, &BFR[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				BFR[--padd_start] = extra_c;
			BFR[1] = '0';
			BFR[2] = 'x';
			return (write(1, &BFR[padd_start], i - padd_start) +
				write(1, &BFR[ind], length - (1 - padd_start) - 2));
		}
	}
	BFR[--ind] = 'x';
	BFR[--ind] = '0';
	if (extra_c)
		BFR[--ind] = extra_c;
	return (write(1, &BFR[ind], BUFF_SIZE - ind - 1));
}
