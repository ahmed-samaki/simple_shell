#include "shell.h"

/**
 * initialize_info - Initializes the info_t struct.
 * @info: Pointer to the info_t struct to initialize.
 */
void initialize_info(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * populate_info - Populates the info_t struct with command information.
 * @info: Pointer to the info_t struct to populate.
 * @args: Command arguments.
 */
void populate_info(info_t *info, char **args)
{
    int i = 0;

    info->fname = args[0];
    if (info->arg)
    {
        info->argv = strtow(info->arg, " \t");
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_alias(info);
        replace_vars(info);
    }
}

/**
 * free_info - Frees memory allocated for fields in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @free_all: Flag indicating whether to free all fields or not.
 */
void free_info(info_t *info, int free_all)
{
    ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (free_all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            free_list(&(info->env));
        if (info->history)
            free_list(&(info->history));
        if (info->alias)
            free_list(&(info->alias));
        ffree(info->environ);
        info->environ = NULL;
        bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        _putchar(BUF_FLUSH);
    }
}

