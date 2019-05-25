/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_separators
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "tokenizer.h"

static void delete_token_sep(struct token_node **token_list)
{
    struct token_node *tmp;

    if (!(*token_list))
        return;
    tmp = (*token_list)->next;
    if ((*token_list) && (*token_list)->next)
        (*token_list)->next->prev = NULL;
    if ((*token_list) && (*token_list)->prev)
        (*token_list)->prev->next = NULL;
    free((*token_list));
    (*token_list) = tmp;
}

static void check_token_list_sep(struct token_node *token_list)
{
    while (token_list) {
        if (DELIM_TYPE(token_list->id) == T_SEPARATOR) {
            delete_token_sep(&token_list);
            continue;
        }
        if (token_list)
            token_list = token_list->next;
    }
}

struct cmd_s *delete_separators(struct cmd_s *list)
{
    struct cmd_s *head = list;
    struct token_node *token_list;

    while (list) {
        token_list = list->token_list;
        check_token_list_sep(token_list);
        list = list->next;
    }
    return head;
}