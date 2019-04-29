/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Restores the given env variable
*/

#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "minishell.h"

void restore_var_path(my_env_t *env, char *var, char *restore)
{
    char *command = my_strcat(my_strdup("setenv "), my_strdup(var));
    char **argv;

    command = my_strcat(command, my_strdup(" "));
    command = my_strcat(command, my_strdup(restore));
    argv = my_str_towordarray(command, " \t");
    free(command);
    set_env(argv, env);
    my_free_fields(argv);
}
