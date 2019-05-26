/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** alias
*/

#include <stdlib.h>
#include "shell.h"
#include "my_string.h"

static int new_alias(int ac, char *name, char **cmd,
struct alias_s alias[MAX_ALIAS])
{
    char *new_cmd = my_strdup("");
    int index = find_alias(alias, name);

    if (new_cmd == NULL || index == -1)
        return -1;
    for (int i = 0; i < ac; i++) {
        new_cmd = my_strcat_freeleft(new_cmd, cmd[i]);
        if (new_cmd == NULL)
            return -1;
        if (i + 1 < ac)
            new_cmd = my_strcat_freeleft(new_cmd, " ");
        if (new_cmd == NULL)
            return -1;
    }
    alias[index].name = my_strdup(name);
    alias[index].command = my_strdup(new_cmd);
    if (alias[index].name == NULL || alias[index].command == NULL)
        return -1;
    free(new_cmd);
    return 0;
}

static int change_alias(int ac, int index, char **cmd,
struct alias_s alias[MAX_ALIAS])
{
    char *new_cmd = my_strdup("");

    if (new_cmd == NULL)
        return -1;
    for (int i = 0; i < ac; i++) {
        new_cmd = my_strcat_freeleft(new_cmd, cmd[i]);
        if (new_cmd == NULL)
            return -1;
        if (i + 1 < ac)
            new_cmd = my_strcat_freeleft(new_cmd, " ");
        if (new_cmd == NULL)
            return -1;
    }
    free(alias[index].command);
    alias[index].command = my_strdup(new_cmd);
    if (alias[index].command == NULL)
        return -1;
    return 0;
}

static int add_alias(int ac, char *name, char **cmd,
struct alias_s alias[MAX_ALIAS])
{
    int index = find_alias(alias, name);

    if (index == -1)
        return full_alias();
    else if (alias[index].name == NULL) {
        return new_alias(ac, name, cmd, alias);
    } else {
        return change_alias(ac, index, cmd, alias);
    }
}

int my_alias(struct my_shell *shell, char **av)
{
    int ac = my_strarraylen(av);

    if (ac == 1)
        display_aliases(shell->aliases);
    else if (ac == 2) {
        display_one_alias(shell->aliases, av[1]);
    } else {
        return add_alias(ac - 2, av[1], av + 2, shell->aliases);
    }
    return 0;
}