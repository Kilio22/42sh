/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_redirections_type_conditions
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "parser.h"

int check_red_type_conditions_input(struct token_node **token,
struct pipe_s *pipe)
{
    if (!(*token)->next || (*token)->next->id != ID_TEXT)
        return fprintf(stderr, "Missing name for redirect.\n"), -1;
    else if (check_already_redirect(pipe, 0, 4) == -1 || pipe->next)
        return fprintf(stderr, "Ambiguous output redirect.\n"), -1;
    else {
        pipe->redirections[(*token)->id - ID_DB_FULL_RREDIRECTION] =
strdup((*token)->next->content);
        if (pipe->redirections[(*token)->id - ID_DB_FULL_RREDIRECTION] == NULL)
            return -1;
    }
    return 0;
}

int check_red_type_conditions_output(struct token_node **token,
struct pipe_s *pipe)
{
    if (!(*token)->next || (*token)->next->id != ID_TEXT)
        return fprintf(stderr, "Missing name for redirect.\n"), -1;
    else if (check_already_redirect(pipe, 5, 6) == -1 || pipe->prev)
        return fprintf(stderr, "Ambiguous input redirect.\n"), -1;
    else {
        pipe->redirections[(*token)->id - ID_DB_FULL_RREDIRECTION] =
strdup((*token)->next->content);
        if (pipe->redirections[(*token)->id - ID_DB_FULL_RREDIRECTION] == NULL)
            return -1;
    }
    return 0;
}
