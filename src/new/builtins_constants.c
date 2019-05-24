/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** buidins_constants
*/

#include "shell.h"
#include "parser.h"
//#include "builtins.h"

const struct builtins_s *builtins[] = {
    {"cd", "change the current working directory"},
    {"env", "displays the env"},
    {"yes", "loop and displays y or the args"},
    {"echo", "displays the given arguments"},
    {"exit", "exit the shell with the given return value"},
    {"alias", "display aliases, or add a new one for a command"},
    {"snake", "launch the snake game"},
    {"where", "displays all known instances of command."},
    {"which", "displays the real command that the shell execute"},
    {"setenv", "set a new env variable or change an existing one"},
    {"whoami", "displays who you are"},
    {"history", "displays the history of commands"},
    {"unalias", "remove one or more aliases"},
    {"builtins", "displays all shell built-in"},
    {"unsetenv", "unset one or more env variable(s)"},
    NULL
};