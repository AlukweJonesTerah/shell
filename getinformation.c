#include "shell.h"

/**
 * custom_clear_info - initializes custom_info_t struct
 * @custom_info: struct address
 */
void custom_clear_info(custom_info_t *custom_info)
{
	custom_info->custom_arg = NULL;
	custom_info->custom_argv = NULL;
	custom_info->custom_path = NULL;
	custom_info->custom_argc = 0;
}
/**
 * custom_set_info - initializes custom_info_t struct
 * @custom_info: struct address
 * @custom_av: custom argument vector
 */
void custom_set_info(custom_info_t *custom_info, char **custom_av)
{
	int i = 0;

	custom_info->custom_fname = custom_av[0];
	if (custom_info->custom_arg)
	{
		custom_info->custom_argv = custom_strtow(custom_info->custom_arg, " \t");
		if (!custom_info->custom_argv)
		{
			custom_info->custom_argv = custom_malloc(sizeof(char *) * 2);
			if (custom_info->custom_argv)
			{
				custom_info->custom_argv[0] = custom_strdup(custom_info->custom_arg);
				custom_info->custom_argv[1] = NULL;
			}
		}
		for (i = 0; custom_info->custom_argv && custom_info->custom_argv[i]; i++)
			;
		custom_info->custom_argc = i;
		custom_replace_alias(custom_info);
		custom_replace_vars(custom_info);
	}
}

/**
 * custom_free_info - frees custom_info_t struct fields
 * @custom_info: struct address
 * @all: true if freeing all fields
 */
void custom_free_info(custom_info_t *custom_info, int all)
{
	custom_ffree(custom_info->custom_argv);
	custom_info->custom_argv = NULL;
	custom_info->custom_path = NULL;

	if (all)
	{
		if (!custom_info->custom_cmd_buf)
			custom_free(custom_info->custom_arg);
		if (custom_info->custom_env)
			custom_free_list(&(custom_info->custom_env));
		if (custom_info->custom_history)
			custom_free_list(&(custom_info->custom_history));
		if (custom_info->custom_alias)
			custom_free_list(&(custom_info->custom_alias));
		custom_ffree(custom_info->custom_environ);
		custom_info->custom_environ = NULL;
		custom_bfree((void **)custom_info->custom_cmd_buf);
		if (custom_info->custom_readfd > 2)
			close(custom_info->custom_readfd);
		custom_putchar(BUF_FLUSH);
	}
}
