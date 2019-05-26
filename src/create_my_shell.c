/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_my_shell
*/

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "shell.h"

static void dup_env(char **env, struct my_shell *shell)
{
    size_t len = my_strarraylen(env);
    char **new_env = malloc(sizeof(char *) * (len + 1));

    if (!new_env) {
        shell->env = NULL;
        return;
    }
    new_env[len] = NULL;
    for (size_t i = 0; env[i]; i++) {
        new_env[i] = strdup(env[i]);
        if (!new_env[i]) {
            shell->env = NULL;
            return;
        }
    }
    shell->env = new_env;
    shell->local_env = malloc(sizeof(char *));
    if (!shell->local_env)
        return;
    shell->local_env[0] = NULL;
}

static int init_aliases(struct my_shell *shell)
{
    init_alias(shell->aliases);
    return 0;
}

struct my_shell *create_my_shell(char const **env)
{
    struct my_shell *shell = malloc(sizeof(struct my_shell));

    if (!shell)
        return NULL;
    dup_env((char **) env, shell);
    if (!shell->env || !shell->local_env)
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
    if (init_aliases(shell) == -1)
        return NULL;
    return shell;
}
