#include "shell.h"
/**
 * custom_get_environ - returns the string array copy of our custom environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **custom_get_environ(custom_info_t *info)
{
	if (!info->custom_environ || info->env_changed)
	{
		info->custom_environ = custom_list_to_strings(info->custom_env);
		info->env_changed = 0;
	}
	return (info->custom_environ);
}

/**
 * custom_unsetenv - Remove a custom environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string custom env var property
 */
int custom_unsetenv(custom_info_t *info, char *var)
{
	custom_list_t *node = info->custom_env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = custom_delete_node_at_index(&(info->custom_env), i);
			i = 0;
			node = info->custom_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * custom_setenv - Initialize a new custom environment variable,
 *                 or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string custom env var property
 * @value: the string custom env var value
 * Return: Always 0
 */
int custom_setenv(custom_info_t *info, char *var, char *value)
{
	char *buf = NULL;
	custom_list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = custom_malloc(custom_strlen(var) + custom_strlen(value) + 2);
	if (!buf)
		return (1);
	custom_strcpy(buf, var);
	custom_strcat(buf, "=");
	custom_strcat(buf, value);
	node = info->custom_env;
	while (node)
	{
		p = custom_starts_with(node->str, var);
		if (p && *p == '=')
		{
			custom_free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	custom_add_node_end(&(info->custom_env), buf, 0);
	custom_free(buf);
	info->env_changed = 1;
	return (0);
}
