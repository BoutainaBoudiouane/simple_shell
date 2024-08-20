#include "main.h"

/**
 * read_history - Reads historical data from a file.
 * @info: Pointer to info_t struct.
 * Return: the number of lines read from the history file.
 */
int read_history(info_t *info)
{
	int j, last_idx = 0, line_count = 0;
	ssize_t fd, read_len, file_size  = 0;
	struct stat file_stat;
	char *file_content = NULL, *file_path = get_history_file(info);

	if (!file_path)
		return (0);
	_memset((void *)file_path, 0, sizeof(char *));
	fd = open(file_path, O_RDONLY);
	free(file_path);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	file_content = malloc(file_size + 1);
	if (!file_content)
		return (0);
	read_len = read(fd, file_content, file_size);
	file_content[file_size] = '\0';
	if (read_len <= 0)
		return (free(file_content), 0);
	close(fd);
	for (j = 0; j < file_size; j++)
		if (file_content[j] == '\n')
		{
			file_content[j] = '\0';
			build_history_list(info, file_content + last_idx, line_count++);
			last_idx = j + 1;
		}
	if (last_idx != j)
		build_history_list(info, file_content + last_idx, line_count++);
	free(file_content);
	info->history_count = line_count;
	while (info->history_count-- >= HIST_SIZE)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->history_count);
}

/**
 * get_history_file - Constructs full path to history file.
 * @info: Ptr to info_t struct.
 * Return: Ptr to dynamically allocated string with full path,
 *         or NULL if history file path cannot be constructed.
 */
char *get_history_file(info_t *info)
{
	char *histo_path = NULL, *dir = NULL;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	histo_path = malloc(sizeof(char) *
			(str_length(dir) + str_length(HIST_FILE) + 2));
	if (!histo_path)
		return (NULL);
	_memset((void *)histo_path, 0, sizeof(char *));
	histo_path[0] = '\0';
	str_n_cpy(histo_path, dir, str_length(dir));
	str_n_cat(histo_path, "/", str_length("/"));
	str_n_cat(histo_path, HIST_FILE, str_length(HIST_FILE));
	return (histo_path);
}

/**
 * build_history_list - Builds a history list with the provided data.
 * @info: Pointer to info_t struct.
 * @buf: String data to add to history.
 * @line_count: Line count to associate with the data.
 * Return: 0 on success.
 */
int build_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = info->history ? info->history : NULL;

	add_node_end(&node, buf, line_count);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Updates the numbering of history nodes.
 * @info: Pointer to info_t struct.
 * Return: the updated history count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j;

	for (j = 0; node; j++, node = node->next)
		node->num = j;
	return (info->history_count = j);
}

/**
 * write_history - Writes history data to a file.
 * @info: Pointer to info_t struct.
 * Return: 1 on success, or -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *file_path = get_history_file(info);
	list_t *node = NULL;

	if (!file_path)
		return (-1);
	_memset((void *)file_path, 0, sizeof(char *));
	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_path);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_str_fd(node->str, fd);
		print_chr_fd('\n', fd);
	}
	print_chr_fd(EOF, fd);
	close(fd);
	return (1);
}
