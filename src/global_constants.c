/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Contains global variables
*/

#include "minishell.h"

const my_funcptrs_t builtins[5] = {
    {"exit", exit_shell},
    {"env", display_env},
    {"setenv", set_env},
    {"unsetenv", unset_env},
    {"cd", change_active_dir}
};

const char *CHAR_WORDS = "&|<>;()";
