/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** add_node
*/

#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

int add_node(struct token_node *head, enum delim_ids id, char *ptr, ssize_t n)
{
    struct token_node *last;
    struct token_node *new;

    if (!head->content) {
        head->id = id;
        head->content = strndup(ptr, n);
        if (!head->content)
            return -1;
        return 0;
    }
    last = get_last_node(head);
    new = create_node(id, last);
    if (!new)
        return -1;
    new->content = strndup(ptr, n);
    if (!new->content)
        return -1;
    if (last)
        last->next = new;
    return 0;
}
