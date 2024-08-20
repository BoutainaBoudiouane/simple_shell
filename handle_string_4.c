#include "main.h"

/**
 * str_to_word - Splits a string into words based on delimiters.
 * @string: The input string.
 * @delimiter: The string containing delimiters.
 * Return: A dynamically allocated array of strings, or NULL on failure.
 */
char **str_to_word(const char *string, char *delimiter)
{
	int nb_words, i, j, k, m;
	char **str = NULL;

	if (!string || string[0] == '\0')
		return (NULL);
	delimiter = !delimiter ? " " : delimiter;
	nb_words = num_words(string, delimiter);
	if (!nb_words)
		return (NULL);
	str = malloc((nb_words + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; i < nb_words; i++)
	{
		while (is_delimiter(string[j], delimiter))
			j++;
		k = 0;
		while (!is_delimiter(string[j + k], delimiter) && string[j + k] != '\0')
			k++;
		str[i] = malloc((k + 1) * sizeof(char));
		if (!str[i])
		{
			for (k = 0; k < i; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str[i][m] = string[j++];
		str[i][m] = '\0';
	}
	str[i] = NULL;
	return (str);
}

/**
 * num_words - Counts the number of words in a string.
 * @string: The input string.
 * @delimiter: The string containing delimiters.
 * Return: The number of words.
 */
int num_words(const char *string, const char *delimiter)
{
	int j = 0, nb_words = 0;

	for (; string[j] != '\0'; j++)
		if (!is_delimiter(string[j], delimiter) &&
		(is_delimiter(string[j + 1], delimiter) || string[j + 1] == '\0'))
			nb_words++;
	return (nb_words);
}

/**
 * is_delimiter - Checks if a character is a delimiter.
 * @character: The character to check.
 * @delimiter: The string containing delimiters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(const char character, const char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == character)
			return (1);
	return (0);
}

/**
 * *str_cpy - copies the string pointer to by src.
 * @src: source string
 * @dest: destination to copy the string
 * Return: string
 */
char *str_cpy(char *dest, const char *src)
{
	int j = -1;

	if (dest == src || src == NULL)
		return (dest);
	do {
		j++;
		dest[j] = src[j];
	} while (src[j] != '\0');
	dest[j] = 0;
	return (dest);
}
