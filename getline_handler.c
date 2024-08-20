#include "main.h"

/**
 * input_buf - Read input from the user and handle buffer management
 * @info: Pointer to the info_t structure
 * @buf: Pointer to the input buffer
 * @len: Pointer to the buffer length
 * Return: Number of characters read, -1 on error or end of input
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		y = _getline(info, buf, &len_p);
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
				(*buf)[y - 1] = '\0', y--;
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->history_count++);
			*len = y;
			info->cmd_buf = buf;
		}
	}
	return (y);
}

/**
 * get_input - Reads input and handles command chaining
 * @info: Pointer to info_t structure
 * Return: Number of characters read, -1 on failure
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, k, len;
	ssize_t y = 0;
	char **buf_p = &(info->arg), *p;

	print_char(EOF);
	y = input_buf(info, &buf, &len);
	if (y == -1)
		return (-1);
	if (len)
	{
		k = i;
		p = buf + i;
		check_chain(info, buf, &k, i, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}
		i = k + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = NORM_CMD;
		}
		*buf_p = p;
		return (str_length(p));
	}
	*buf_p = buf;
	return (y);
}

/**
 * read_buf - Reads data from file descriptor into buffer
 * @info: Pointer to info_t structure
 * @buf: Buffer to store read data
 * @i: Pointer to current index in buffer
 * Return: Number of bytes read, 0 on buffer already filled, -1 on failure
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t byte_read  = 0;

	if (*i)
		return (0);
	byte_read  = read(info->readfd, buf, BUF_SIZE);
	if (byte_read  >= 0)
		*i = byte_read;
	return (byte_read);
}

/**
 * _getline - Reads a line from input and appends to buffer
 * @info: The info_t structure
 * @ptr: Pointer to the buffer
 * @length: Length of the buffer
 * Return: Number of characters read (including newline), -1 on failure
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t read = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (j == len)
		j = len = 0;

	read = read_buf(info, buf, &len);
	if (read == -1 || (read == 0 && len == 0))
		return (-1);

	c = str_chr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (size)
		str_n_cat(new_p, buf + j, k - j);
	else
		str_n_cpy(new_p, buf + j, k - j + 1);

	size += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return (size);
}

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C)
 * @sig_num: The signal number (unused)
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	print_string("\n$ ");
	print_char(EOF);
}
