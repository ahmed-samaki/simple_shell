#include "shell.h"

/**
 * bfree - Safely deallocates memory and sets the pointer to NULL
 * @ptr: A pointer to the pointer to be freed
 *
 * This function frees the memory pointed to by 'ptr' and then sets 'ptr' to NULL.
 *
 * Return: 1 if memory was freed, 0 if 'ptr' or its data is already NULL.
 */
int bfree(void **ptr)
{
    // Check if the pointer 'ptr' is not NULL and the data it points to is not NULL
    if (ptr && *ptr)
    {
        // Free the memory occupied by the data pointed to by 'ptr'
        free(*ptr);

        // Set 'ptr' itself to NULL to avoid a dangling pointer
        *ptr = NULL;

        // Memory has been successfully freed
        return 1;
    }

    // If 'ptr' is already NULL or it points to NULL data, no action is taken
    return 0;
}

