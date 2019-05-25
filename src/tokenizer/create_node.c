/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_node
*/

#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

struct token_node *create_node(enum delim_ids id, struct token_node *prev)
{
    struct token_node *new = malloc(sizeof(struct token_node));

    if (!new)
        return NULL;
    new->content = NULL;
    new->id = id;
    new->next = NULL;
    new->prev = prev;
    return new;
}