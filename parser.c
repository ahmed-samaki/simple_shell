#include "shell.h"

/**
 * is_executable - Checks if a file is an executable command.
 * @info: Pointer to the info struct.
 * @file_path: Path to the file.
 *
 * Return: 1 if it's an executable command, 0 otherwise.
 */
int is_executable(info_t *info, char *file_path)
{
    struct stat file_stat;

    (void)info; // Unused parameter, avoids a compiler warning.
    
    if (!file_path || stat(file_path, &file_stat))
        return 0;

    // Check if the file is a regular file (executable).
    if (file_stat.st_mode & S_IFREG)
        return 1;

    return 0;
}

/**
 * extract_chars - Extracts characters from a string.
 * @source_str: The source string.
 * @start_idx: Starting index.
 * @end_idx: Ending index.
 *
 * Return: Pointer to a new buffer containing the extracted characters.
 */
char *extract_chars(char *source_str, int start_idx, int end_idx)
{
    static char extracted_buf[1024];
    int source_idx = 0, extracted_idx = 0;

    for (extracted_idx = 0, source_idx = start_idx; source_idx < end_idx; source_idx++)
    {
        if (source_str[source_idx] != ':')
            extracted_buf[extracted_idx++] = source_str[source_idx];
    }
    
    extracted_buf[extracted_idx] = 0;
    return extracted_buf;
}

/**
 * find_command_path - Finds the full path of a command in the PATH string.
 * @info: Pointer to the info struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_command_path(info_t *info, char *path_str, char *command)
{
    int path_idx = 0, curr_pos = 0;
    char *full_path;

    if (!path_str)
        return NULL;

    // Check if the command starts with "./" and is executable.
    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_executable(info, command))
            return command;
    }

    while (1)
    {
        if (!path_str[path_idx] || path_str[path_idx] == ':')
        {
            // Extract a path segment from path_str.
            full_path = extract_chars(path_str, curr_pos, path_idx);
            
            if (!*full_path)
                _strcat(full_path, command);
            else
            {
                _strcat(full_path, "/");
                _strcat(full_path, command);
            }
            
            // Check if the constructed path is an executable command.
            if (is_executable(info, full_path))
                return full_path;

            if (!path_str[path_idx])
                break;

            curr_pos = path_idx;
        }
        
        path_idx++;
    }

    return NULL; // Command not found in the PATH.
}

