#include "shell.h"

/**
 * display_history - Displays the history list, one command per line,
 *                   preceded by line numbers starting at 0.
 * @info: Pointer to the info struct.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Unsets an alias.
 * @info: Pointer to the info struct.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *equals_ptr, saved_char;
	int ret;

	equals_ptr = _strchr(str, '=');
	if (!equals_ptr)
		return (1);
	saved_char = *equals_ptr;
	*equals_ptr = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equals_ptr = saved_char;
	return (ret);
}

/**
 * set_alias - Sets an alias.
 * @info: Pointer to the info struct.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *equals_ptr;

	equals_ptr = _strchr(str, '=');
	if (!equals_ptr)
		return (1);
	if (!*++equals_ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equals_ptr = NULL, *alias_ptr = NULL;

	if (node)
	{
		equals_ptr = _strchr(node->str, '=');
		for (alias_ptr = node->str; alias_ptr <= equals_ptr; alias_ptr++)
			_putchar(*alias_ptr);
		_putchar('\'');
		_puts(equals_ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Mimics the alias builtin (man alias).
 * @info: Pointer to the info struct.
 *
 * Return: Always 0.
 */
int shell_alias(info_t *info)
{
	int i = 0;
	char *equals_ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals_ptr = _strchr(info->argv[i], '=');
		if (equals_ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

