/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_node
*/

#include <stdlib.h>
#include "tokenizer.h"

void delete_node(struct token_node *ptr)
{
    free(ptr->content);
    free(ptr);
}

void delete_token_node_list(struct token_node *head)
{
    struct token_node *tmp = head;

    while (head) {
        head = head->next;
        delete_node(tmp);
        tmp = head;
    }
}
