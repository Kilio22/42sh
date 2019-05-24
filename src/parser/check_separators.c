/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** check_separators
*/

#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"

int check_sep(struct token_node *head)
{
    if (head->id == ID_OR && !head->next)
        return fprintf(stderr, "Invalid null command.\n"), -1;
    if (head->id == ID_AND && head->prev &&
head->prev->id != ID_AND && head->prev->id != ID_NOWAIT
&& (head->next && (head->next->id != ID_TEXT && (head->next->id < 7
|| head->next->id > 12))))
        return fprintf(stderr, "Invalid null command.\n"), -1;
    if ((head->id == ID_OR && ((!head->prev) ||
(head->prev->id != ID_TEXT || (head->next->id != ID_TEXT
&& (head->next->id < 7 || head->next->id > 12))))))
        return fprintf(stderr, "Invalid null command.3\n"), -1;
    return 0;
}