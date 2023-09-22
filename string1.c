#include "shell.h"

/**
 * string_copy - Copies a string.
 * @destination: The destination buffer.
 * @source: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *string_copy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';
	return (destination);
}

/**
 * string_duplicate - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}

/**
 * print_string - Prints a string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		write_character(str[index]);
		index++;
	}
}

/**
 * write_character - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char c)
{
	static int buffer_index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || buffer_index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != BUFFER_FLUSH)
		buffer[buffer_index++] = c;

	return (1);
}

