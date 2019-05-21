/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_token_list_from_line
*/

#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "delimiters.h"

int find_token_type(char *line)
{
    for (size_t i = 0; delim_tab[i]; i++) {
        if (!strncmp(line, delim_tab[i]->delim, strlen(delim_tab[i]->delim)))
            return delim_tab[i]->type;
    }
    return T_WITHOUT;
}

struct token_node *create_token_list_from_line(char *line)
{
    struct token_node *head = NULL;
    size_t i = 0;

    while (line[i]) {

    }
    free(line);
    return head;
}
