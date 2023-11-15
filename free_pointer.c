#include "shell.h"
/**
 * free_pointer - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed and success, else 0.
 */
int free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
