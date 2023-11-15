#include "shell.h"
/**
 * custom_is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @custom_path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int custom_is_cmd(custom_info_t *info, char *custom_path)
{
	struct stat st;

	(void)info;
	if (!custom_path || stat(custom_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * custom_dup_chars - duplicates characters
 * @custom_pathstr: the PATH string
 * @custom_start: starting index
 * @custom_stop: stopping index
 * Return: pointer to new buffer
 */
char *custom_dup_chars(char *custom_pathstr, int custom_start, int custom_stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = custom_start; i < custom_stop; i++)
		if (custom_pathstr[i] != ':')
			buf[k++] = custom_pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * custom_find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @custom_pathstr: the PATH string
 * @custom_cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *custom_find_path(custom_info_t *info, char *custom_pathstr, char *custom_cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!custom_pathstr)
		return (NULL);
	if ((_strlen(custom_cmd) > 2) && starts_with(custom_cmd, "./"))
	{
		if (custom_is_cmd(info, custom_cmd))
			return (custom_cmd);
	}
	while (1)
	{
		if (!custom_pathstr[i] || custom_pathstr[i] == ':')
		{
			path = custom_dup_chars(custom_pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, custom_cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, custom_cmd);
			}
			if (custom_is_cmd(info, path))
				return (path);
			if (!custom_pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
