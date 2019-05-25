/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** which
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_stdio.h"
#include "shell.h"

static void find_which_path(char *command, char **env)
{
    char **path = my_str_towordarray(env[find_var_index("PATH", env)], ":");
    char *str = NULL;

    for (size_t i = 0; path[i] != NULL; i++) {
        str = my_strcat_nofree(path[i], "/");
        if (str == NULL)
            continue;
        str = my_strcat_freeleft(str, command);
        if (str == NULL)
            continue;
        if (access(str, F_OK) == 0) {
            puts(str);
            free(str);
            return free_path(path);
        }
        free(str);
    }
    free_path(path);
    fprintf(stderr, "%s: Command not found.\n", command);
}

int my_which(int argc, char **av, char **env)
{
    if (argc < 2) {
        fprintf(stderr, "%s: Too few arguments.\n", av[0]);
        return -1;
    }
    for (size_t i = 1; i < (size_t) argc; i++) {
        if (is_a_builtin(av[i]) == true)
            my_printf("%s: shell built-in command.\n");
        else
            find_which_path(av[i], env);
    }
    return 0;
}