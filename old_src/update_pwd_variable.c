/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** update_pwd_variable
*/

#include <linux/limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "my_string.h"
#include "my_stdio.h"
#include "minishell.h"

void update_previous_pwd(my_env_t *env)
{
    int index = find_var_index("OLD_PWD", env->env);
    int pwd_index = find_var_index("PWD", env->env);
    char *new_path;

    if (index == -1) {
        restore_var_path(env, "OLD_PWD", DEFAULT_HOME);
        index = find_var_index("OLD_PWD", env->env);
    }
    if (pwd_index == -1) {
        restore_var_path(env, "PWD", DEFAULT_HOME);
        pwd_index = find_var_index("PWD", env->env);
    }
    new_path = my_strdup(&env->env[pwd_index][4]);
    free(env->env[index]);
    env->env[index] = my_strcat(my_strdup("OLD_PWD="), new_path);
}

void update_new_pwd(my_env_t *env)
{
    int index = find_var_index("PWD", env->env);
    char buf[PATH_MAX] = {0};

    if (getcwd(buf, PATH_MAX) == NULL) {
        my_dprintf(2, "cd: %s.\n", strerror(errno));
        buf[0] = '/';
        buf[1] = '\0';
    }
    free(env->env[index]);
    env->env[index] = my_strcat(my_strdup("PWD="), my_strdup(buf));
}