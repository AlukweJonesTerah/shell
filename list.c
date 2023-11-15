#include "shell.h"

/**
 * custom_add_node - adds a node to the start of the list
 * @custom_head: address of pointer to head node
 * @custom_str: str field of node
 * @custom_num: node index used by history
 *
 * Return: size of list
 */
custom_list_t *custom_add_node(custom_list_t **custom_head,
const char *custom_str, int custom_num)
{
	custom_list_t *new_custom_head;

	if (!custom_head)
		return (NULL);
	new_custom_head = malloc(sizeof(custom_list_t));
	if (!new_custom_head)
		return (NULL);
	custom_memset((void *)new_custom_head, 0, sizeof(custom_list_t));
	new_custom_head->num = custom_num;
	if (custom_str)
	{
		new_custom_head->str = custom_strdup(custom_str);
		if (!new_custom_head->str)
		{
			free(new_custom_head);
			return (NULL);
		}
	}
	new_custom_head->next = *custom_head;
	*custom_head = new_custom_head;
	return (new_custom_head);
}

/**
 * custom_add_node_end - adds a node to the end of the list
 * @custom_head: address of pointer to head node
 * @custom_str: str field of node
 * @custom_num: node index used by history
 *
 * Return: size of list
 */
custom_list_t *custom_add_node_end(custom_list_t **custom_head,
const char *custom_str, int custom_num)
{
	custom_list_t *new_custom_node, *custom_node;

	if (!custom_head)
		return (NULL);
	custom_node = *custom_head;
	new_custom_node = malloc(sizeof(custom_list_t));
	if (!new_custom_node)
		return (NULL);
	custom_memset((void *)new_custom_node, 0, sizeof(custom_list_t));
	new_custom_node->num = custom_num;
	if (custom_str)
	{
		new_custom_node->str = custom_strdup(custom_str);
		if (!new_custom_node->str)
		{
			free(new_custom_node);
			return (NULL);
		}
	}
	if (custom_node)
	{
		while (custom_node->next)
			custom_node = custom_node->next;
		custom_node->next = new_custom_node;
	}
	else
		*custom_head = new_custom_node;
	return (new_custom_node);
}

/**
 * custom_print_list_str - prints only the str element
 * of a custom_list_t linked list
 * @custom_h: pointer to first node
 *
 * Return: size of list
 */
size_t custom_print_list_str(const custom_list_t *custom_h)
{
	size_t i = 0;

	while (custom_h)
	{
		custom_puts(custom_h->str ? custom_h->str : "(nil)");
		custom_puts("\n");
		custom_h = custom_h->next;
		i++;
	}
	return (i);
}

/**
 * custom_delete_node_at_index - deletes node at given index
 * @custom_head: address of pointer to first node
 * @custom_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int custom_delete_node_at_index(custom_list_t **custom_head,
unsigned int custom_index)
{
	custom_list_t *custom_node, *custom_prev_node;
	unsigned int i = 0;

	if (!custom_head || !*custom_head)
		return (0);
	if (!custom_index)
	{
		custom_node = *custom_head;
		*custom_head = (*custom_head)->next;
		free(custom_node->str);
		free(custom_node);
		return (1);
	}
	custom_node = *custom_head;
	while (custom_node)
	{
		if (i == custom_index)
		{
			custom_prev_node->next = custom_node->next;
			free(custom_node->str);
			free(custom_node);
			return (1);
		}
		i++;
		custom_prev_node = custom_node;
		custom_node = custom_node->next;
	}
	return (0);
}

/**
 * custom_free_list - frees all nodes of a list
 * @custom_head_ptr: address of pointer to head node
 *
 * Return: void
 */
void custom_free_list(custom_list_t **custom_head_ptr)
{
	custom_list_t *custom_node, *custom_next_node, *custom_head;

	if (!custom_head_ptr || !*custom_head_ptr)
		return;
	custom_head = *custom_head_ptr;
	custom_node = custom_head;
	while (custom_node)
	{
		custom_next_node = custom_node->next;
		free(custom_node->str);
		free(custom_node);
		custom_node = custom_next_node;
	}
	*custom_head_ptr = NULL;
}
