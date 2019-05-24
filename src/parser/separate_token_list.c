/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** separate_token_list
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "tokenizer.h"

static struct cmd_s *init_cmd_list(struct token_node *tokens)
{
    struct cmd_s *list = malloc(sizeof(struct cmd_s));
    struct token_node *head = tokens;

    if (!list || !tokens)
        return NULL;
    list->next = NULL;
    list->prev = NULL;
    list->pipe = NULL;
    if (DELIM_TYPE(tokens->id) == T_SEPARATOR)
        list->token_list = NULL;
    else
        list->token_list = head;
    list->id = 0;
    return list;
}

static int add_cmd(struct cmd_s *list, struct token_node *add)
{
    struct cmd_s *new;
    struct cmd_s *last = get_last_cmd(list);

    if (!add)
        return 0;
    new = malloc(sizeof(struct cmd_s));
    if (!new)
        return -1;
    new->next = NULL;
    new->id = add->id - 2;
    new->pipe = NULL;
    if (DELIM_TYPE(add->id) == T_SEPARATOR &&
(!add->next || DELIM_TYPE(add->next->id) == T_SEPARATOR))
        new->token_list = NULL;
    else
        new->token_list = add->next;
    new->prev = last;
    last->next = new;
    return 0;
}

struct cmd_s *separate_token_list(struct token_node *head)
{
    int n_return = 0;
    struct cmd_s *list = init_cmd_list(head);

    if (!list)
        return NULL;
    while (head) {
        if (DELIM_TYPE(head->id) == T_SEPARATOR)
            n_return = add_cmd(list, head);
        if (n_return == -1)
            return NULL;
        if (head)
            head = head->next;
    }
    return delete_separators(list);
}
