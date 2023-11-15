#include "shell.h"
/**
 * _custom_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _custom_exit(custom_info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exit_check = _custom_err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_custom_eputs(info->argv[1]);
			_custom_eputchar('\n');
			return (1);
		}
		info->err_num = _custom_err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _custom_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_cd(custom_info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		target_dir = _custom_getenv(info, "HOME=");
		if (!target_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((target_dir = _custom_getenv(info, "PWD=")) ? target_dir : "/");
		else
			chdir_ret = chdir(target_dir);
	}
	else if (_custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!_custom_getenv(info, "OLDPWD="))
		{
			_custom_puts(current_dir);
			_custom_putchar('\n');
			return (1);
		}
		_custom_puts(_custom_getenv(info, "OLDPWD=")), _custom_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((target_dir = _custom_getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_custom_eputs(info->argv[1]), _custom_eputchar('\n');
	}
	else
	{
		_custom_setenv(info, "OLDPWD", _custom_getenv(info, "PWD="));
		_custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _custom_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _custom_help(custom_info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_custom_puts("help call works. Function not yet implemented \n");
	if (0)
		_custom_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

