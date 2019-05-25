/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils_builtins
*/

#include <stdbool.h>
#include <stdlib.h>
#include "shell.h"
#include "my.h"
#include "my_string.h"

char *my_strcat_freeleft(const char *left, const char *right)
{
    size_t len = my_strlen(left);
    char *new = malloc(len + my_strlen(right) + 1);

    if (!left || !right || !new)
        return (NULL);
    my_strcpy(new, left);
    my_strcpy(&new[len], right);
    free((char *) left);
    return (new);
}

bool is_a_builtin(const char *str)
{
    for (int i = 0; builtins[i].name != NULL; i++)
        if (my_strcmp(str, builtins[i].name) == 0)
            return true;
    return false;
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

void free_path(char **path)
{
    for (size_t i = 0; path[i] != NULL; i++)
        free(path[i]);
    free(path);
}