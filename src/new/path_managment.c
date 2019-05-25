/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** path_managment
*/

#include <unistd.h>
#include "my_string.h"
#include "parser.h"
#include "shell.h"

static int restore_path(struct my_shell *shell)
{
    char buffer[1024] = {0};
    size_t len = 0;

    if (confstr(_CS_PATH, buffer, 1024) == 0)
        return -1;
    return my_setenv(shell, "PATH", buffer);
}

char *get_cmd_path(char *cmd, struct my_shell *shell)
{
    char *path = my_getenv(shell, "PATH");
    char **diff_path = NULL;

    if (!path) {
        if (restore_path(shell) == -1)
            return NULL;
        path = my_getenv(shell, "PATH");
        if (!path)
            return NULL;
    }
    diff_path = my_str_towordarray(path, ":");
    for (size_t i = 0; diff_path[i]; i++) {
        path = my_strcat_nofree(diff_path[i], cmd);
        if (access(path, F_OK))
            return path;
        free(path);
    }
    return NULL;
}