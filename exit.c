#include "shell.h"
/**
 * _custom_strncpy - copies a string
 * @custom_dest: the destination string to be copied to
 * @custom_src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_custom_strncpy(char *custom_dest, char *custom_src, int n)
{
	int i, j;
	char *s = custom_dest;

	i = 0;
	while (custom_src[i] != '\0' && i < n - 1)
	{
		custom_dest[i] = custom_src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			custom_dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _custom_strncat - concatenates two strings
 * @custom_dest: the first string
 * @custom_src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_custom_strncat(char *custom_dest, char *custom_src, int n)
{
	int i, j;
	char *s = custom_dest;

	i = 0;
	j = 0;
	while (custom_dest[i] != '\0')
		i++;
	while (custom_src[j] != '\0' && j < n)
	{
		custom_dest[i] = custom_src[j];
		i++;
		j++;
	}
	if (j < n)
		custom_dest[i] = '\0';
	return (s);
}

/**
 * _custom_strchr - locates a character in a string
 * @custom_s: the string to be parsed
 * @custom_c: the character to look for
 * Return: (custom_s) a pointer to the memory area s
 */
char *_custom_strchr(char *custom_s, char custom_c)
{
	do {
		if (*custom_s == custom_c)
			return (custom_s);
	} while (*custom_s++ != '\0');

	return (NULL);
}
