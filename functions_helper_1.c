#include "main.h"

/**
 * interactive - Checks if the program is running interactively.
 * @info: Pointer to the info_t structure.
 * Return: 1 if the program is running interactively, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _err_atoi - Converts a string to an integer.
 * @string: The input string.
 * Return: The integer value if successful, or -1 on error.
 */
int _err_atoi(const char *string)
{
	int j = 0;
	unsigned long int res = 0;

	if (*string == '+')
		string++;
	for (j = 0; string[j] != '\0'; j++)
	{
		if (string[j] >= 48 && string[j] <= 57)
		{
			res *= 10;
			res += (string[j] - 48);
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - Prints an error message to standard error output.
 * @info: Pointer to the info_t structure containing relevant information.
 * @error: The error string to print.
 */
void print_err(info_t *info, const char *error)
{
	print_err_string(info->file_name);
	print_err_string(": ");
	print_int(info->line_count, STDERR_FILENO);
	print_err_string(": ");
	print_err_string(info->argv[0]);
	print_err_string(": ");
	print_err_string(error);
}

/**
 * print_int - Prints an integer to a file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */
int print_int(int input, int fd)
{
	int (*put_char)(int) = print_char;
	int j, c = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		put_char = print_err_char;

	if (input < 0)
	{
		abs_value = (unsigned int)(-input);
		put_char('-');
		c++;
	}
	else
		abs_value = (unsigned int) input;
	current = abs_value;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs_value / j)
			put_char(48 + current / j), c++;
		current %= j;
	}
	put_char(48 + current);
	c++;
	return (c);
}
