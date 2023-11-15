#include "shell.h"
/**
 * _custom_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _custom_env(custom_info_t *info)
{
	print_list_str(info->custom_env);
	return (0);
}

/**
 * _custom_getenv - gets the value of a custom environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_custom_getenv(custom_info_t *info, const char *name)
{
	custom_list_t *node = info->custom_env;
	char *p;

	while (node)
	{
		p = custom_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _custom_setenv - Initialize a new custom environment variable,
 *                  or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _custom_setenv(custom_info_t *info)
{
	if (info->argc != 3)
	{
		_custom_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _custom_unsetenv - Remove a custom environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _custom_unsetenv(custom_info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_custom_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_custom_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populate_custom_env_list - populates custom env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_custom_env_list(custom_info_t *info)
{
	custom_list_t *node = NULL;
	size_t i;

	for (i = 0; custom_environ[i]; i++)
		custom_add_node_end(&node, custom_environ[i], 0);
	info->custom_env = node;
	return (0);
}
