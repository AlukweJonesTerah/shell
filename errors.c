#include "shell.h"
/**
 * _custom_eputs - prints an input string to stderr
 * @str: the string to be printed
 * Return: Nothing
 */
void _custom_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_custom_eputchar(str[i]);
		i++;
	}
}

/**
 * _custom_eputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _custom_eputchar(char c)
{
	static int i;
	static char buf[CUSTOM_WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != CUSTOM_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _custom_putfd - writes the character c to a given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _custom_putfd(char c, int fd)
{
	static int i;
	static char buf[CUSTOM_WRITE_BUF_SIZE];

	if (c == CUSTOM_BUF_FLUSH || i >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != CUSTOM_BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _custom_putsfd - prints an input string to a given fd
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * Return: the number of characters put
 */
int _custom_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _custom_putfd(*str++, fd);
	}
	return (i);
}
