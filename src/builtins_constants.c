/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** buidins_constants
*/

#include "shell.h"

const struct builtins_s builtins[] = {
    {"cd", "change the current working directory", my_cd},
    {"env", "displays the env", my_env},
    {"yes", "loop and displays y or the args", my_yes},
    {"echo", "displays the given arguments", echo},
    {"exit", "exit the shell with the given return value", my_exit},
    {"alias", "display aliases, or add a new one for a command", my_alias},
    {"where", "displays all known instances of command.", my_where},
    {"which", "displays the real command that the shell execute", my_which},
    {"setenv", "set a new env variable or change an existing one", my_setenv},
    {"whoami", "displays who you are", my_whoami},
    {"unalias", "remove one or more aliases", my_unalias},
    {"builtins", "displays all shell built-in", display_builtins},
    {"unsetenv", "unset one or more env variable(s)", my_unsetenv},
    {"set", "display local env", my_set},
    {"unset", "unset one or more local variable(s)", my_unset},
    {"repeat", "repeats the given command N times", my_repeat},
    {NULL, NULL, NULL}
};