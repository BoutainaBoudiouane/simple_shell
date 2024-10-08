#include "main.h"

/**
 * clear_info - Initializes info_t struct
 * @info: Struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int j = 0;

	info->file_name = av[0];
	if (info->arg)
	{
		info->argv = str_to_word(info->arg, "\t\a\r\n ");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees memory associated with fields of the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: True if all fields should be freed.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->env_strings);
		info->env_strings = NULL;
		Null_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		print_char(EOF);
	}
}
