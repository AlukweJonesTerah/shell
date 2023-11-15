#include "shell.h"
/**
 **custom_memset - fills memory with a constant byte
 *@custom_s: the pointer to the memory area
 *@custom_b: the byte to fill *custom_s with
 *@custom_n: the amount of bytes to be filled
 *Return: (custom_s) a pointer to the memory area custom_s
 */
char *custom_memset(char *custom_s, char custom_b, unsigned int custom_n)
{
	unsigned int i;

	for (i = 0; i < custom_n; i++)
		custom_s[i] = custom_b;
	return (custom_s);
}

/**
 * custom_ffree - frees a string of strings
 * @custom_pp: string of strings
 */
void custom_ffree(char **custom_pp)
{
	char **a = custom_pp;

	if (!custom_pp)
		return;
	while (*custom_pp)
		free(*custom_pp++);
	free(a);
}

/**
 * custom_realloc - reallocates a block of memory
 * @custom_ptr: pointer to previous malloc'ated block
 * @custom_old_size: byte size of previous block
 * @custom_new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *custom_realloc(void *custom_ptr, unsigned int custom_old_size, unsigned int custom_new_size)
{
	char *p;

	if (!custom_ptr)
		return (malloc(custom_new_size));
	if (!custom_new_size)
		return (free(custom_ptr), NULL);
	if (custom_new_size == custom_old_size)
		return (custom_ptr);

	p = malloc(custom_new_size);
	if (!p)
		return (NULL);

	custom_old_size = custom_old_size < custom_new_size ? custom_old_size : custom_new_size;
	while (custom_old_size--)
		p[custom_old_size] = ((char *)custom_ptr)[custom_old_size];
	free(custom_ptr);
	return (p);
}
