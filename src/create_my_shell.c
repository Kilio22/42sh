/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_my_shell
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "shell.h"

static char **dup_env(char **env)
{
    size_t len = my_strarraylen(env);
    char **new_env = malloc(sizeof(char *) * (len + 1));

    if (!new_env)
        return NULL;
    new_env[len] = NULL;
    for (size_t i = 0; env[i]; i++)
        new_env[i] = env[i];
    return new_env;
}

static int init_history_and_alias(struct my_shell *shell)
{
    shell->history = malloc(sizeof(struct breakpoints_s));
    if (shell->history == NULL)
        return -1;
    if (init_history(shell->history) == -1)
        return -1;
    init_alias(shell->aliases);
    return 0;
}

struct my_shell *create_my_shell(char const **env)
{
    struct my_shell *shell = malloc(sizeof(struct my_shell));

    if (!shell)
        return NULL;
    shell->env = dup_env((char **) env);
    if (!shell->env)
        return NULL;
    shell->fd_save[SAVE_STDIN] = dup(STDIN_FILENO);
    shell->fd_save[SAVE_STDOUT] = dup(STDOUT_FILENO);
    shell->fd_save[SAVE_STDERR] = dup(STDERR_FILENO);
    if (shell->fd_save[SAVE_STDIN] == -1 || shell->fd_save[SAVE_STDOUT] == -1 ||
shell->fd_save[SAVE_STDERR] == -1)
        return NULL;
    shell->pgid = getpgid(getpid());
    if (shell->pgid == -1)
        return NULL;
    shell->n_return = 0;
    if (init_history_and_alias(shell) == -1)
        return NULL;
    return shell;
}
