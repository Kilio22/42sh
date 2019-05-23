/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** separate_cmd_list
*/

#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

static struct pipe_s *init_pipe_list(struct token_node *tokens)
{
    struct pipe_s *list = malloc(sizeof(struct cmd_s));
    struct token_node *head = tokens;

    if (!list)
        return NULL;
    list->next = NULL;
    list->prev = NULL;
    if (tokens->id == ID_PIPE)
        list->token_list = NULL;
    else
        list->token_list = head;
    return list;
}

static struct pipe_s *get_last_pipe(struct pipe_s *head)
{
    if (!head)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

static int add_pipe(struct pipe_s *list, struct token_node *add)
{
    struct pipe_s *new = new = malloc(sizeof(struct cmd_s));
    struct pipe_s *last = get_last_pipe(list);

    if (!add)
        return 0;
    if (!new)
        return -1;
    new->next = NULL;
    if (add->id == ID_PIPE && (!add->next || add->next->id == ID_PIPE))
        new->token_list = NULL;
    else
        new->token_list = add->next;
    new->prev = last;
    last->next = new;
    return 0;
}

struct pipe_s *pipe_token_list(struct token_node *token)
{
    int n_return = 0;
    struct pipe_s *list = init_pipe_list(token);

    if (!list)
        return NULL;
    while (token) {
        if (token->id == ID_PIPE)
            n_return = add_pipe(list, token);
        if (n_return == -1)
            return NULL;
        if (token)
            token = token->next;
    }
    return delete_pipe(list);
}
