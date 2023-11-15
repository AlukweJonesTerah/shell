#include "shell.h"

/**
 * custom_hsh - main shell loop
 * @custom_info: the parameter & return info struct
 * @custom_av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int custom_hsh(custom_info_t *custom_info, char **custom_av)
{
	ssize_t custom_r = 0;
	int custom_builtin_ret = 0;

	while (custom_r != -1 && custom_builtin_ret != -2)
	{
		clear_info(custom_info);
		if (interactive(custom_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		custom_r = get_input(custom_info);
		if (custom_r != -1)
		{
			set_info(custom_info, custom_av);
			custom_builtin_ret = custom_find_builtin(custom_info);
			if (custom_builtin_ret == -1)
				custom_find_cmd(custom_info);
		}
		else if (interactive(custom_info))
			_putchar('\n');
		free_info(custom_info, 0);
	}
	write_history(custom_info);
	free_info(custom_info, 1);
	if (!interactive(custom_info) && custom_info->status)
		exit(custom_info->status);
	if (custom_builtin_ret == -2)
	{
		if (custom_info->err_num == -1)
			exit(custom_info->status);
		exit(custom_info->err_num);
	}
	return (custom_builtin_ret);
}

/**
 * custom_find_builtin - finds a builtin command
 * @custom_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int custom_find_builtin(custom_info_t *custom_info)
{
	int i, custom_built_in_ret = -1;
	custom_builtin_table custom_builtintbl[] = {
		{"exit", custom_myexit},
		{"env", custom_myenv},
		{"help", custom_myhelp},
		{"history", custom_myhistory},
		{"setenv", custom_mysetenv},
		{"unsetenv", custom_myunsetenv},
		{"cd", custom_mycd},
		{"alias", custom_myalias},
		{NULL, NULL}
	};

	for (i = 0; custom_builtintbl[i].type; i++)
		if (_strcmp(custom_info->argv[0], custom_builtintbl[i].type) == 0)
		{
			custom_info->line_count++;
			custom_built_in_ret = custom_builtintbl[i].func(custom_info);
			break;
		}
	return (custom_built_in_ret);
}

/**
 * custom_find_cmd - finds a command in PATH
 * @custom_info: the parameter & return info struct
 *
 * Return: void
 */
void custom_find_cmd(custom_info_t *custom_info)
{
	char *path = NULL;
	int i, k;

	custom_info->path = custom_info->argv[0];
	if (custom_info->linecount_flag == 1)
	{
		custom_info->line_count++;
		custom_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; custom_info->arg[i]; i++)
		if (!is_delim(custom_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = custom_find_path(custom_info, _getenv(custom_info, "PATH="), custom_info->argv[0]);
	if (path)
	{
		custom_info->path = path;
		custom_fork_cmd(custom_info);
	}
	else
	{
		if ((interactive(custom_info) || _getenv(custom_info, "PATH=")
			|| custom_info->argv[0][0] == '/') && is_cmd(custom_info, custom_info->argv[0]))
			custom_fork_cmd(custom_info);
		else if (*(custom_info->arg) != '\n')
		{
			custom_info->status = 127;
			print_error(custom_info, "not found\n");
		}
	}
}

/**
 * custom_fork_cmd - forks a an exec thread to run cmd
 * @custom_info: the parameter & return info struct
 *
 * Return: void
 */
void custom_fork_cmd(custom_info_t *custom_info)
{
	pid_t custom_child_pid;

	custom_child_pid = fork();
	if (custom_child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (custom_child_pid == 0)
	{
		if (execve(custom_info->path, custom_info->argv, get_environ(custom_info)) == -1)
		{
			free_info(custom_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(custom_info->status));
		if (WIFEXITED(custom_info->status))
		{
			custom_info->status = WEXITSTATUS(custom_info->status);
			if (custom_info->status == 126)
				print_error(custom_info, "Permission denied\n");
		}
	}
}

