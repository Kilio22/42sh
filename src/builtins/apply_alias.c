/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** apply_alias
*/

#include "shell.h"
#include "my_string.h"

int apply_alias(struct token_node *node, struct alias_s aliases[MAX_ALIAS])
{
    int index = find_alias(aliases, node->content);

    if (index == -1 || aliases[index].name == NULL)
        return 0;
    else {
        free(node->content);
        node->content = my_strdup(aliases[index].command);
        if (node->content == NULL)
            return -1;
    }
    return 0;
}