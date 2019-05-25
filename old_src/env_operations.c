/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** All about that env variable
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_string.h"
#include "minishell.h"

void free_env(my_env_t *env)
{
    my_free_fields(env->env);
    free(env);
}

static int my_varlen(const char *str)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != '=')
        i++;
    return (i);
}

int find_var_index(char *var, char **env)
{
    int len = my_strlen(var);
    int big_len;
    int i;

    for (i = 0; env[i] != 0; i++) {
        big_len = my_varlen(env[i]);
        big_len = (len > big_len) ? len : big_len;
        if (my_strncmp(var, env[i], big_len) == 0)
            return (i);
    }
    return (-1);
}

void enlarge_env(my_env_t *env)
{
    int len = my_strarraylen(env->env);
    char **new_env = malloc(sizeof(char *) * (len + 1 + ENV_EXTRASIZE));
    int i = 0;

    if (new_env == NULL) {
        perror("sorry dude");
        exit(84);
    }
    env->blocks = ENV_EXTRASIZE;
    while (env->env[i] != 0) {
        new_env[i] = env->env[i];
        i++;
    }
    new_env[i] = 0;
    free(env->env);
    env->env = new_env;
}

my_env_t *init_my_env(char *real_env[])
{
    int len = my_strarraylen(real_env);
    char **my_env = malloc(sizeof(char *) * (len + 1 + ENV_EXTRASIZE));
    my_env_t *env = malloc(sizeof(my_env_t));
    int i = 0;

    if (env == NULL || my_env == NULL)
        return (NULL);
    env->blocks = ENV_EXTRASIZE;
    while (real_env[i] != 0) {
        my_env[i] = my_strdup(real_env[i]);
        if (my_env[i] == NULL)
            return (NULL);
        i++;
    }
    my_env[i] = 0;
    env->env = my_env;
    return (env);
}
