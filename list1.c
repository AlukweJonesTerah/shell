#include "shell.h"
/**
 * custom_list_len - determines length of linked list
 * @current_node: pointer to the current node
 * Return: size of list
 */
size_t custom_list_len(const custom_list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * custom_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **custom_list_to_strings(custom_list_t *head)
{
	custom_list_t *current_node = head;
	size_t size = custom_list_len(head), index;
	char **strings_array;
	char *str;

	if (!head || !size)
		return (NULL);

	strings_array = malloc(sizeof(char *) * (size + 1));
	if (!strings_array)
		return (NULL);

	for (index = 0; current_node; current_node = current_node->next, index++)
	{
		str = malloc(_strlen(current_node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < index; j++)
				free(strings_array[j]);
			free(strings_array);
			return (NULL);
		}

		str = _strcpy(str, current_node->str);
		strings_array[index] = str;
	}

	strings_array[index] = NULL;
	return (strings_array);
}


/**
 * custom_print_list - prints all elements of a custom_list_t linked list
 * @current_node: pointer to current node
 *
 * Return: size of list
 */
size_t custom_print_list(const custom_list_t *current_node)
{
	size_t count = 0;

	while (current_node)
	{
		_puts(convert_number(current_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(current_node->str ? current_node->str : "(nil)");
		_puts("\n");
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * custom_node_starts_with - returns node whose string starts with prefix
 * @current_node: pointer to current node
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
custom_list_t *custom_node_starts_with(custom_list_t *
current_node, char *prefix, char c)
{
	char *p = NULL;

	while (current_node)
	{
		p = starts_with(current_node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * custom_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @target_node: pointer to the target node
 *
 * Return: index of node or -1
 */
ssize_t custom_get_node_index(custom_list_t *head, custom_list_t *target_node)
{
	size_t index = 0;

	while (head)
	{
		if (head == target_node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

