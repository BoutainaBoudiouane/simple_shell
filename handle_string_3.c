#include "main.h"

/**
 * str_n_cpy - function that copies a string
 * @dest: destination string
 * @src: source string
 * @length: number of bytes of @src
 * Return: @dest
 */
char *str_n_cpy(char *dest, const char *src, size_t length)
{
	size_t j;

	for (j = 0; j < length - 1 && src[j] != '\0'; j++)
		dest[j] = src[j];
	while (j < length)
		dest[j++] = '\0';
	return (dest);
}

/**
 * str_n_cat - function that concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @length: most number bytes from src
 * Return: @dest
 */
char *str_n_cat(char *dest, const char *src, int length)
{
	int len = str_length(dest), j;

	for (j = 0; j < length && src[j]; j++)
		dest[len + j] = src[j];
	if (j < length)
		dest[len + j] = '\0';
	return (dest);
}

/**
 * str_chr - function that locates a character in a string
 * @string: the string to search in
 * @character: the character to search for
 * Return: the pointer to the first occurrence or null
 */
char *str_chr(char *string, const char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');
	return (NULL);
}

/**
 * dup_str - Duplicate a substring of characters from @string.
 * @string: Source string.
 * @start: Index to start copying from.
 * @end: Index to stop copying at.
 * Return: Pointer to the duplicated substring.
 */
char *dup_str(const char *string, int start, int end)
{
	int x, y;
	char *buf = malloc(BUF_SIZE);

	_memset((void *)buf, 0, BUF_SIZE);
	if (!buf)
		return (NULL);
	for (x = start, y = 0; x < end && y < BUF_SIZE - 1; x++)
		if (string[x] != ':')
			buf[y++] = string[x];
	buf[y] = '\0';
	return (buf);
}
