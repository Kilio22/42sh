/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** delete_pipe
*/

#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

static void delete_token_pipe(struct token_node **token_list)
{
    struct token_node *tmp;

    tmp = (*token_list)->next;
    if ((*token_list) && (*token_list)->next)
        (*token_list)->next->prev = NULL;
    if ((*token_list) && (*token_list)->prev)
        (*token_list)->prev->next = NULL;
    free((*token_list));
    (*token_list) = tmp;
}

static void check_token_list_pipe(struct token_node *token_list)
{
    while (token_list) {
        if (token_list->id == ID_PIPE) {
            delete_token_pipe(&token_list);
            continue;
        }
        if (token_list)
            token_list = token_list->next;
    }
}

struct pipe_s *delete_pipe(struct pipe_s *list)
{
    struct pipe_s *head = list;
    struct token_node *token_list;

    while (list) {
        token_list = list->token_list;
        check_token_list_pipe(token_list);
        list = list->next;
    }
    return head;
}