/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Changes the current directory
*/

#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

static char *get_home_path(my_env_t *env)
{
    int index = find_var_index("HOME", env->env);
    char *path;

    if (index == -1) {
        restore_var_path(env, "HOME", DEFAULT_HOME);
        index = find_var_index("HOME", env->env);
    }
    path = my_strdup(&env->env[index][5]);
    return (path);
}

static char *get_previous_dir(my_env_t *env)
{
    int index = find_var_index("OLD_PWD", env->env);

    if (index == -1) {
        restore_var_path(env, "OLD_PWD", DEFAULT_HOME);
        index = find_var_index("OLD_PWD", env->env);
    }
    return (my_strdup(&env->env[index][8]));
}

static char *get_newdir_path(char *path, my_env_t *env)
{
    if (path == NULL)
        return (get_home_path(env));
    if (my_strcmp(path, "-") == 0)
        return (get_previous_dir(env));
    if (access(path, F_OK) == -1) {
        my_dprintf(2, "%s: %s.\n", path, strerror(errno));
        return (NULL);
    }
    return (my_strdup(path));
}

void change_active_dir(char **argv, my_env_t *env)
{
    char *path;
    int ndir;

    path = get_newdir_path(argv[1], env);
    if (path == NULL)
        return;
    ndir = chdir(path);
    if (ndir == -1) {
        my_dprintf(2, "%s: %s.\n", path, strerror(errno));
        return;
    }
    update_previous_pwd(env);
    update_new_pwd(env);
    free(path);
}
