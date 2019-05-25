/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** which
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_string.h"
#include "my_stdio.h"
#include "builtins.h"

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

int my_which(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);

    if (ac < 2) {
        fprintf(stderr, "%s: Too few arguments.\n", av[0]);
        return -1;
    }
    for (size_t i = 1; i < (size_t) ac; i++) {
        if (is_a_builtin(av[i]) == true)
            my_printf("%s: shell built-in command.\n");
        else
            find_which_path(av[i], shell->env);
    }
    return 0;
}