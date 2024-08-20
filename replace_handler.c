#include "main.h"

/**
 * replace_alias - Replaces a command with its alias
 * @info: Pointer to the info_t struct
 * Return: 1 on success, 0 on failure
 */
int replace_alias(info_t *info)
{
	int attemp;
	list_t *alias_node;
	char *alias_value;

	for (attemp = 0; attemp < 10; attemp++)
	{
		alias_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!alias_node)
			return (0);
		free(info->argv[0]);
		alias_value = str_chr(alias_node->str, '=');
		if (!alias_value)
			return (0);
		alias_value = str_dup(alias_value + 1);
		if (!alias_value)
			return (0);
		info->argv[0] = alias_value;
	}
	return (1);
}

/**
 * replace_vars - Replaces environment variables in command arguments
 * @info: Pointer to the info_t struct
 * Return: Always returns 0
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *env_node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;
		if (!str_cmp(info->argv[j], "$?"))
		{
			str_rpl(&(info->argv[j]),
						   str_dup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[j], "$$"))
		{
			str_rpl(&(info->argv[j]),
						   str_dup(convert_number(getpid(), 10, 0)));
			continue;
		}
		env_node = node_starts_with(info->env, &info->argv[j][1], '=');
		if (env_node)
		{
			str_rpl(&(info->argv[j]),
						   str_dup(str_chr(env_node->str, '=') + 1));
			continue;
		}
		str_rpl(&info->argv[j], str_dup(""));
	}
	return (0);
}
