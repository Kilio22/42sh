/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_redirections
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

static int check_red_type_conditions(struct token_node **token,
struct pipe_s *pipe)
{
    if ((*token)->id >= ID_DB_FULL_RREDIRECTION && (*token)->id
<= ID_RREDIRECTION) {
        if (check_red_type_conditions_input(token, pipe) == -1)
            return -1;
    } else {
        if (check_red_type_conditions_output(token, pipe) == -1)
            return -1;
    }
    if (!pipe->redirections[(*token)->id - ID_DB_FULL_RREDIRECTION])
        return -1;
    return 0;
}

static int check_redirections_type(struct token_node **token,
struct pipe_s *pipe)
{
    struct token_node *save;

    if (check_red_type_conditions(token, pipe) == -1)
        return -1;
    save = (*token);
    (*token)->prev->next = (*token)->next->next;
    if ((*token)->next->next)
        (*token)->next->next->prev = (*token)->prev;
    (*token) = (*token)->next->next;
    free(save->next);
    return 0;
}

static int check_first_conditions(struct token_node **head,
struct pipe_s *pipe)
{
    if (!(*head)->next || (*head)->next->id != ID_TEXT)
        return fprintf(stderr, "Missing name for redirect.\n"), -1;
    if ((*head)->id >= ID_DB_LREDIRECTION
&& (*head)->id <= ID_LREDIRECTION && (pipe->prev
|| check_already_redirect(pipe, 5, 6) == -1))
        return fprintf(stderr, "Ambiguous input redirect.\n"), -1;
    else if ((*head)->id >= ID_DB_FULL_RREDIRECTION &&
(*head)->id <= ID_RREDIRECTION && (pipe->next
|| check_already_redirect(pipe, 0, 4) == -1))
        return fprintf(stderr, "Ambiguous output redirect.\n"), -1;
    if (!(*head)->next->next)
        return fprintf(stderr, "Invalid null command.\n"), -1;
    return 0;
}

static int check_first_redirections(struct token_node **head,
struct pipe_s *pipe)
{
    if ((*head)->id < ID_DB_FULL_RREDIRECTION || (*head)->id > ID_LREDIRECTION)
        return 0;
    if (check_first_conditions(head, pipe) == -1)
        return -1;
    pipe->redirections[(*head)->id - ID_DB_FULL_RREDIRECTION]
= strdup((*head)->next->content);
    if (!pipe->redirections[(*head)->id - ID_DB_FULL_RREDIRECTION])
        return -1;
    (*head) = (*head)->next->next;
    free((*head)->prev->prev);
    free((*head)->prev);
    (*head)->prev = NULL;
    pipe->token_list = (*head);
    if ((*head) && (*head)->id >= ID_DB_FULL_RREDIRECTION &&
(*head)->id <= ID_LREDIRECTION)
        return check_first_redirections(head, pipe);
    return 0;
}

int check_redirections(struct token_node *head, struct pipe_s *pipe)
{
    int n_return = 0;

    if (!head)
        return fprintf(stderr, "Invalid null command.\n"), -1;
    if (check_first_redirections(&head, pipe) == -1)
        return -1;
    for (; head; head = head->next) {
        if (head->id >= ID_DB_FULL_RREDIRECTION && head->id <= ID_LREDIRECTION)
            n_return = check_redirections_type(&head, pipe);
        if (n_return == -1)
            return -1;
        if (!head)
            return 0;
    }
    return 0;
}