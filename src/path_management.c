/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** path_managment
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "my_string.h"
#include "shell.h"

static int restore_path(struct my_shell *shell)
{
    char buffer[1024] = {0};

    if (confstr(_CS_PATH, buffer, 1024) == 0)
        return -1;
    return set_env(shell, "PATH", buffer);
}

static char *check_restore_path(struct my_shell *shell)
{
    char *path;

    if (restore_path(shell) == -1)
        return NULL;
    path = my_getenv(shell, "PATH");
    if (!path)
        return NULL;
    return path;
}

char *get_cmd_path(char *cmd, struct my_shell *shell)
{
    char *path = my_getenv(shell, "PATH");
    char **diff_path = NULL;

    if (!path) {
        path = check_restore_path(shell);
        if (!path)
            return NULL;
    }
    diff_path = my_str_towordarray(path, ":");
    if (!diff_path)
        return NULL;
    for (size_t i = 0; diff_path[i]; i++) {
        if (diff_path[i][strlen(diff_path[i]) - 1] != '/')
            diff_path[i] = my_strcat_freeleft(diff_path[i], "/");
        path = my_strcat_nofree(diff_path[i], cmd);
        if (!access(path, F_OK))
            return my_free_fields(diff_path), path;
        free(path);
    }
    return my_free_fields(diff_path), NULL;
}