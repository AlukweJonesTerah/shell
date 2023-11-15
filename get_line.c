#include "shell.h"
/**
 * custom_input_buf - buffers chained commands
 * @custom_info: parameter struct
 * @custom_buf: address of buffer
 * @custom_len: address of len var
 *
 * Return: bytes read
 */
ssize_t custom_input_buf(custom_info_t *
custom_info, char **custom_buf, size_t *custom_len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*custom_len) /* if nothing left in the buffer, fill it */
	{
		/* custom_bfree((void **)custom_info->custom_cmd_buf); */
		free(*custom_buf);
		*custom_buf = NULL;
		signal(SIGINT, custom_sigintHandler);
#if USE_GETLINE
		r = getline(custom_buf, &len_p, stdin);
#else
		r = custom_getline(custom_info, custom_buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*custom_buf)[r - 1] == '\n')
			{
				(*custom_buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			custom_info->custom_linecount_flag = 1;
			custom_remove_comments(*custom_buf);
			custom_build_history_list(
			custom_info, *custom_buf, custom_info->custom_histcount++);
			/* if (_strchr(*custom_buf, ';')) is this a command chain? */
			{
				*custom_len = r;
				custom_info->custom_cmd_buf = custom_buf;
			}
		}
	}
	return (r);
}

/**
 * custom_get_input - gets a line minus the newline
 * @custom_info: parameter struct
 * Return: bytes read
 */
ssize_t custom_get_input(custom_info_t *custom_info)
{
	static char *custom_buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(custom_info->custom_arg), *p;

	custom_putchar(BUF_FLUSH);
	r = custom_input_buf(custom_info, &custom_buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = custom_buf + i; /* get pointer for return */
		custom_check_chain(custom_info, custom_buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (custom_is_chain(custom_info, custom_buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			custom_info->custom_cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* pass back pointer to current command position */
		return (custom_strlen(p)); /* return length of current command */
	}

	*buf_p = custom_buf; /* else not a*/
/*chain, pass back buffer from custom_getline() */
	return (r); /* return length of buffer from custom_getline() */
}

/**
 * custom_read_buf - reads a buffer
 * @custom_info: parameter struct
 * @custom_buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t custom_read_buf(custom_info_t *
custom_info, char *custom_buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(custom_info->custom_readfd, custom_buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @custom_info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int custom_getline(custom_info_t *custom_info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = custom_read_buf(custom_info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = custom_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = custom_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		custom_strncat(new_p, buf + i, k - i);
	else
		custom_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * custom_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void custom_sigintHandler(__attribute__((unused))int sig_num)
{
	custom_puts("\n");
	custom_puts("$ ");
	custom_putchar(BUF_FLUSH);
}
