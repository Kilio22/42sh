/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** apply_alias
*/

#include "shell.h"
#include "my_string.h"

static void fix_nodes(struct token_node **node, struct token_node *new)
{
    struct token_node *head = new;

    new->prev = (*node)->prev;
    if ((*node)->prev != NULL)
        (*node)->prev->next = new;
    while (new->next != NULL)
        new = new->next;
    new->next = (*node)->next;
    if ((*node)->next != NULL)
        (*node)->next->prev = new;
    free((*node)->content);
    free(*node);
    *node = head;
}

int apply_alias(struct token_node **node, struct alias_s aliases[MAX_ALIAS])
{
    int index;
    struct token_node *new;

    if (*node == NULL)
        return -1;
    index = find_alias(aliases, (*node)->content);
    if (index == -1 || aliases[index].name == NULL)
        return -1;
    else {
        new = create_token_list_from_line(aliases[index].command);
        if (new == NULL)
            return -1;
        fix_nodes(node, new);
    }
    return 0;
}