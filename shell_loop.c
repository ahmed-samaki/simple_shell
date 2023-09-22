#include "shell.h"

/**
 * shell_loop - Main shell loop.
 * @info: Pointer to the parameter & return info struct.
 * @av: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int shell_loop(info_t *info, char **av)
{
    ssize_t input_result = 0;
    int builtin_result = 0;

    while (input_result != -1 && builtin_result != -2)
    {
        clear_info(info);

        if (is_interactive(info))
            _puts("$ ");

        _eputchar(BUF_FLUSH);
        input_result = get_input(info);

        if (input_result != -1)
        {
            set_info(info, av);
            builtin_result = find_builtin(info);

            if (builtin_result == -1)
                find_command(info);
        }
        else if (is_interactive(info))
            _putchar('\n');

        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (!is_interactive(info) && info->status)
        exit(info->status);

    if (builtin_result == -2)
    {
        if (info->err_num == -1)
            exit(info->status);

        exit(info->err_num);
    }

    return builtin_result;
}

/**
 * find_builtin - Finds a builtin command.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *  0 if builtin executed successfully,
 *  1 if builtin found but not successful,
 *  2 if builtin signals exit().
 */
int find_builtin(info_t *info)
{
    int i;
    int builtin_ret = -1;

    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            builtin_ret = builtintbl[i].func(info);
            break;
        }
    }

    return builtin_ret;
}

/**
 * find_command - Finds a command in PATH.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: void
 */
void find_command(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];

    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    for (i = 0, k = 0; info->arg[i]; i++)
    {
        if (!is_delimiter(info->arg[i], " \t\n"))
            k++;
    }

    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    if (path)
    {
        info->path = path;
        fork_command(info);
    }
    else
    {
        if ((is_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_command(info, info->argv[0]))
            fork_command(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_command - Forks an exec thread to run a command.
 * @info: Pointer to the parameter & return info struct.
 *
 * Return: void
 */
void fork_command(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }

    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);

            if (errno == EACCES)
                exit(126);

            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));

        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);

            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
