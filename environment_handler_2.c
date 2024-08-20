#include "main.h"

/**
 * user_setenv - Handles setting environment variables based on user input.
 * @info: Pointer to the info_t struct.
 * Return: 0 (Success), or 1 (Failure).
 */
int user_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		print_err_string("Usage: setenv VARIABLE_NAME VALUE\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * user_unsetenv - Handles unsetting environment variables based on user input.
 * @info: Pointer to the info_t struct.
 * Return: 0 (Success), or 1 (Failure).
 */
int user_unsetenv(info_t *info)
{
	int var_uns;

	if (info->argc < 2)
	{
		print_err_string(
				"Usage: unsetenv VARIABLE_NAME [VARIABLE_NAME ...]\n"
				);
		return (1);
	}
	for (var_uns = 1 ; info->argc >= var_uns; var_uns++)
		unset_env(info, info->argv[var_uns]);
	return (0);
}

/**
 * populate_env_list - Populates an environment
 *	list with values from the environ array.
 * @info: Pointer to the info_t struct.
 * Return: 0 after populating the list.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j = 0;

	while (environ[j])
		add_node_end(&node, environ[j++], 0);
	info->env = node;
	return (0);
}

/**
 * unset_env - Unsets an environment variable in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @var: The environment variable to unset.
 * Return: 1 if the environment was changed, 0 otherwise.
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *equal_sign_pos;

	if (!node || !var)
		return (0);
	for (; node; j++, node = node->next)
	{
		equal_sign_pos = start_with(node->str, var);
		if (equal_sign_pos && *equal_sign_pos == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			node = info->env;
			j = 0;
			continue;
		}
	}
	return (info->env_changed);
}
