/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_node
*/

#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

struct token_node *create_node(int id, char *content)
{
    struct token_node *new = malloc(sizeof(struct token_node));

    if (!new)
        return NULL;
    new->content = strdup(content);
    if (!new->content)
        return NULL;
    new->id = id;
    new->next = NULL;
    new->prev = NULL;
    return new;
}