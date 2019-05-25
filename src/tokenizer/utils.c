/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** utils
*/

#include <stdlib.h>
#include "tokenizer.h"

struct token_node *get_last_node(struct token_node *head)
{
    while (head->next)
        head = head->next;
    return head;
}

char *slice_string(char **src, size_t index)
{
    char *new = malloc(sizeof(char) * (index + 1));
    size_t i = 0;

    if (!new)
        return NULL;
    for (; (*src)[i] && i < index; i++)
        new[i] = (*src)[i];
    new[i] = '\0';
    for (i = 0; *src && i <= index; i++)
        (*src)++;
    return new;
}

char *cut_string(char **src, size_t index)
{
    char *new = malloc(sizeof(char) * (index + 1));
    size_t i = 0;

    if (!new)
        return NULL;
    for (; (*src)[i] && i < index; i++)
        new[i] = (*src)[i];
    new[i] = '\0';
    for (i = 0; *src && i < index; i++)
        (*src)++;
    return new;
}
