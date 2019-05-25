/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** get_commands
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

static size_t command_len(char ***commands)
{
    size_t i = 0;

    while (*commands++)
        i++;
    return i;
}

static char ***realloc_command_array(char ***commands, char **new)
{
    size_t len = command_len(commands);
    char ***new_array = malloc(sizeof(char **) * (len + 2));

    if (!new_array)
        return NULL;
    for (size_t i = 0; i < len; i++)
        new_array[i] = commands[i];
    new_array[len] = new;
    new_array[len + 1] = NULL;
    free(commands);
    return new_array;
}

static char ***init_commands(void)
{
    char ***commands = malloc(sizeof(char **));

    if (!commands)
        return NULL;
    *commands = NULL;
    return commands;
}

char ***get_commands(my_env_t *env)
{
    char **prompt = get_prompt(env);
    char ***commands = init_commands();
    char **tmp;

    if (!commands)
        exit(84);
    for (size_t i = 0; prompt[i]; i++) {
        tmp = my_str_towordarray(prompt[i], " \t");
        if (!*tmp) {
            my_free_fields(tmp);
            continue;
        }
        commands = realloc_command_array(commands, tmp);
        if (!commands)
            exit(84);
    }
    my_free_fields(prompt);
    return commands;
}
