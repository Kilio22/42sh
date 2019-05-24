/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_token_list_head
*/

#include <stdlib.h>
#include "tokenizer.h"

struct token_node *create_token_list_head(void)
{
    struct token_node *head = malloc(sizeof(struct token_node));

    if (!head)
        return NULL;
    head->content = NULL;
    head->id = ID_TEXT;
    head->next = NULL;
    head->prev = NULL;
    return head;
}
