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
#include "shell.h"

static int get_path(char **path, char *command)
{
    char *str = NULL;
    int occ = 0;

    for (size_t i = 0; path[i] != NULL; i++) {
        str = my_strcat_nofree(path[i], "/");
        if (str == NULL)
            exit(84);
        str = my_strcat_freeleft(str, command);
        if (str == NULL)
            exit(84);
        if (access(str, F_OK) == 0) {
            puts(str);
            occ++;
        }
        free(str);
    }
    return occ;
}

static int find_where_path(char *command, char **env)
{
    int idx = find_var_index("PATH", env);
    char **path = NULL;
    int occ = 0;

    if (idx == -1)
        return 0;
    path = my_str_towordarray(env[idx], ":");
    if (!path)
        exit(84);
    occ = get_path(path, command);
    free_path(path);
    return occ;
}

static int is_an_alias(char *name, struct my_shell *shell)
{
    int index = find_alias(shell->aliases, name);

    if (index == -1 || shell->aliases[index].name == NULL)
        return 0;
    else {
        my_printf("%s is aliased to %s\n", name, shell->aliases[index].command);
        return 1;
    }
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
        occ += is_an_alias(av[i], shell);
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