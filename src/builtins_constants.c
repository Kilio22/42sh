/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** buidins_constants
*/

#include "shell.h"
//#include "builtins.h"

const struct builtins_s builtins[] = {
    {"cd", "change the current working directory", NULL},
    {"env", "displays the env", NULL},
    {"yes", "loop and displays y or the args", NULL},
    {"echo", "displays the given arguments", NULL},
    {"exit", "exit the shell with the given return value", NULL},
    {"alias", "display aliases, or add a new one for a command", NULL},
    {"snake", "launch the snake game", NULL},
    {"where", "displays all known instances of command.", NULL},
    {"which", "displays the real command that the shell execute", NULL},
    {"setenv", "set a new env variable or change an existing one", NULL},
    {"whoami", "displays who you are", NULL},
    {"history", "displays the history of commands", NULL},
    {"unalias", "remove one or more aliases", NULL},
    {"builtins", "displays all shell built-in", NULL},
    {"unsetenv", "unset one or more env variable(s)", NULL}
};