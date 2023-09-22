#include "shell.h"

/**
 * _string_copy - Copies a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_length: The maximum number of characters to be copied.
 *
 * Return: The pointer to the concatenated string.
 */
char *_string_copy(char *destination, char *source, int max_length)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < max_length - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < max_length)
	{
		j = i;
		while (j < max_length)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * _string_concatenate - Concatenates two strings.
 * @destination: The first string.
 * @source: The second string.
 * @max_length: The maximum number of bytes to be used.
 *
 * Return: The pointer to the concatenated string.
 */
char *_string_concatenate(char *destination, char *source, int max_length)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < max_length)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < max_length)
		destination[i] = '\0';
	return (result);
}

/**
 * _string_find_character - Locates a character in a string.
 * @string: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the memory area in 'string' containing 'character',
 *         or NULL if 'character' is not found in 'string'.
 */
char *_string_find_character(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

