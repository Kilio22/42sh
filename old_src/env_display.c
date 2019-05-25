/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Displays the containing of the environement variable
*/

#include "my_stdio.h"
#include "minishell.h"

void display_env(char **argv, my_env_t *env)
{
    (void) argv;
    my_show_wordarray(env->env);
}
