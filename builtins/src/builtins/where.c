/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** where
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_stdio.h"
#include "my_string.h"
#include "builtins.h"

static int find_where_path(char *command, char **env)
{
    char **path = my_str_towordarray(env[find_var_index("PATH", env)], ":");
    char *str = NULL;
    int occ = 0;

    for (size_t i = 0; path[i] != NULL; i++) {
        str = my_strcat_nofree(path[i], "/");
        if (str == NULL)
            continue;
        str = my_strcat_freeleft(str, command);
        if (str == NULL)
            continue;
        if (access(str, F_OK) == 0) {
            puts(str);
            occ++;
        }
        free(str);
    }
    free_path(path);
    return occ;
}

int my_where(struct my_shell *shell, char **av)
{
    int occ = 0;
    int ac = my_strarraylen(av);

    if (ac < 2) {
        fprintf(stderr, "%s: Too few arguments.\n", av[0]);
        return -1;
    }
    for (size_t i = 1; i < (size_t) ac; i++) {
        if (is_a_builtin(av[i]) == true) {
            my_printf("%s is a shell built-in\n");
            occ++;
        }
        occ += find_where_path(av[i], shell->env);
        if (occ == 0)
            my_printf("%s: Command not found.\n", av[i]);
        occ = 0;
    }
    return 0;
}