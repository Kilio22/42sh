/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_syntax
*/

#include <stdlib.h>
#include "parser.h"
#include "tokenizer.h"

static void push_top(struct token_node *node, struct token_node *to_add)
{
    if (!node)
        return;
    while (node->prev)
        node = node->prev;
    node->prev = to_add;
}

int check_syntax(struct token_node *head)
{
    struct token_node *save;

    if (!head)
        return 0;
    save = head->prev;
    head->prev = NULL;
    for (; head; head = head->next) {
        if (head->id == ID_SEPARATOR)
            return push_top(head, save), check_syntax(head->next);
        if (DELIM_TYPE(head->id) == T_SEPARATOR && check_sep(head) == -1)
            return push_top(head, save), -1;
    }
    push_top(head, save);
    return 0;
}