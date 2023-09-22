#include "shell.h"

/**
 * str_length - Returns the length of a string.
 * @str: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int str_length(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    while (*str++)
        length++;

    return (length);
}

/**
 * str_compare - Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int str_compare(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);

        str1++;
        str2++;
    }

    if (*str1 == *str2)
        return (0);
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * str_starts_with - Checks if a string starts with a specified substring.
 * @str: The string to search.
 * @substring: The substring to find.
 *
 * Return: Address of the next character of str if it starts with the substring, or NULL.
 */
char *str_starts_with(const char *str, const char *substring)
{
    while (*substring)
    {
        if (*substring++ != *str++)
            return (NULL);
    }

    return ((char *)str);
}

/**
 * str_concatenate - Concatenates two strings.
 * @destination: The destination buffer.
 * @source: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *str_concatenate(char *destination, char *source)
{
    char *result = destination;

    while (*destination)
        destination++;

    while (*source)
        *destination++ = *source++;

    *destination = *source;
    
    return (result);
}

