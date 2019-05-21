/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** add_node
*/

#include <stdlib.h>
#include "tokenizer.h"

void add_node(struct token_node *head, int id, char *content)
{
    struct token_node *new = create_node(id, content);

    while (head->next)
        head = head->next;
    head->next = new;
    new->prev = head;
}
