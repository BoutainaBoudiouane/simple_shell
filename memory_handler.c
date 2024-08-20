#include "main.h"

/**
 * _memset - Fills the first n bytes of memory with a constant byte.
 * @string: Pointer to the memory area to be filled.
 * @byte: The constant byte to fill the memory with.
 * @length: The number of bytes to fill.
 * Return: A pointer to the memory area @string.
 */
char *_memset(char *string, char byte, unsigned int length)
{
	unsigned int j;

	for (j = 0; j < length; j++)
		string[j] = byte;
	return (string);
}

/**
 * ffree - Frees a double pointer array of strings and the array itself.
 * @pp: Pointer to the array of pointers to strings.
 */
void ffree(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp), pp++;
	free(x);
}

/**
 * Null_free - Frees a pointer and sets it to NULL.
 * @ptr: Pointer to the pointer to be freed.
 * Return: 1 (Success)
 */
int Null_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _realloc - function that reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: size of allocated space for @ptr
 * @new_size: size of the new memory block
 * Return: pointer to the newly allocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *p;
	unsigned int j;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	p = malloc(new_size);
	if (!p)
		return (NULL);
	for (j = 0; j < old_size && j < new_size; j++)
		*((char *)p + j) = *((char *)ptr + j);
	free(ptr);
	return (p);
}
