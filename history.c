#include "shell.h"
/**
 * custom_get_history_file - gets the history file
 * @custom_info: parameter struct
 * Return: allocated string containg history file
 */
char *custom_get_history_file(custom_info_t *info)
{
	char *custom_buf, *custom_dir;

	custom_dir = custom_getenv(info, "HOME=");
	if (!custom_dir)
		return (NULL);
	custom_buf = malloc(sizeof(char) * (custom_strlen(custom_dir)
	+ custom_strlen(CUSTOM_HIST_FILE) + 2));
	if (!custom_buf)
		return (NULL);
	custom_buf[0] = 0;
	custom_strcpy(custom_buf, custom_dir);
	custom_strcat(custom_buf, "/");
	custom_strcat(custom_buf, CUSTOM_HIST_FILE);
	return (custom_buf);
}

/**
 * custom_write_history - creates a file, or appends to an existing file
 * @custom_info: the parameter struct
 * Return: 1 on success, else -1
 */
int custom_write_history(custom_info_t *info)
{
	ssize_t fd;
	char *filename = custom_get_history_file(info);
	custom_list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->custom_history; node; node = node->next)
	{
		custom_putsfd(node->str, fd);
		custom_putfd('\n', fd);
	}
	custom_putfd(CUSTOM_BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * custom_read_history - reads history from file
 * @custom_info: the parameter struc
 * Return: histcount on success, 0 otherwise
 */
int custom_read_history(custom_info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = custom_get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			custom_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		custom_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->custom_histcount = linecount;
	while (custom_info->custom_histcount-- >= CUSTOM_HIST_MAX)
		custom_delete_node_at_index(&(info->custom_history), 0);
	custom_renumber_history(info);
	return (info->custom_histcount);
}

/**
 * custom_build_history_list - adds entry to a history linked list
 * @custom_info: Structure containing potential arguments. Used to maintain
 * @custom_buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int custom_build_history_list(custom_info_t *info,
char *custom_buf, int linecount)
{
	custom_list_t *node = NULL;

	if (custom_info->custom_history)
		node = ->custom_history;
	custom_add_node_end(&node, custom_buf, linecount);
	if (!info->custom_history)
		info->custom_history = node;
	return (0);
}

/**
 * custom_renumber_history - renumbers the history linked list after changes
 * @custom_info: Structure containing potential arguments. Used to maint
 * Return: the new histcount
 */
int custom_renumber_history(custom_info_t *info)
{
	custom_list_t *node = info->custom_history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->custom_histcount = i);
}
