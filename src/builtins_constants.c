/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** buidins_constants
*/

#include "shell.h"
#include "builtins.h"

const struct builtins_s builtins[] = {
    {"cd", "change the current working directory", NULL},
    {"env", "displays the env", NULL},
    {"yes", "loop and displays y or the args", my_yes},
    {"echo", "displays the given arguments", echo},
    {"exit", "exit the shell with the given return value", NULL},
    {"alias", "display aliases, or add a new one for a command", my_alias},
    {"snake", "launch the snake game", snake},
    {"where", "displays all known instances of command.", my_where},
    {"which", "displays the real command that the shell execute", my_which},
    {"setenv", "set a new env variable or change an existing one", my_setenv},
    {"whoami", "displays who you are", my_whoami},
    {"history", "displays the history of commands", print_history},
    {"unalias", "remove one or more aliases", my_unalias},
    {"builtins", "displays all shell built-in", display_builtins},
    {"unsetenv", "unset one or more env variable(s)", my_unsetenv}
};