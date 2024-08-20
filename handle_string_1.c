#include "main.h"

/**
 * print_char - Function to write a character to the standard output.
 * @c: The character to be written.
 * Return: On success, returns 1. Otherwise, returns -1.
 */
int print_char(int c)
{
	static int j;
	static char buf[BUF_SIZE];

	if (c == EOF || j >= BUF_SIZE)
		write(1, buf, j), j = 0;
	if (c != EOF)
		buf[j++] = (char) c;
	return (1);
}

/**
 * print_string - Function to write a null-terminated string
 *              to the standard output.
 * @s: The input string to be written.
 */
void print_string(const char *s)
{
	if (!s)
		return;
	while (*s)
		print_char(*s++);
}

/**
 * str_length - Function to calculate the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int str_length(const char *s)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s++)
		j++;
	return (j);
}
