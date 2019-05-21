/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** add_node
*/

#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

int add_node(struct token_node *head, enum delim_ids id, char *ptr, size_t n)
{
    struct token_node *last = get_last_node(head);
    struct token_node *new = create_node(id, last);

    if (!new)
        return -1;
    new->content = strndup(ptr, n);
    if (!new->content)
        return -1;
    if (last)
        last->next = new;
    return 0;
}
