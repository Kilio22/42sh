/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_token_list_from_line
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

static ssize_t get_container_end(char *ptr, char *end)
{
    for (ssize_t i = 0; ptr[i]; i++) {
        if (!strncmp(ptr + i, end, strlen(end)))
            return i;
    }
    fprintf(stderr, "Unmatched '%s'\n", end);
    return -1;
}

static int analyse_delimiter(struct token_node *head, char *ptr,
                                size_t delim_idx, size_t *n)
{
    ssize_t end_n;

    if (DELIM_TYPE(delim_idx) == T_CONTAINER) {
        end_n = get_container_end(ptr + *n, DELIM_END(delim_idx));
        if (end_n == -1)
            return -1;
        if (add_node(head, DELIM_ID(delim_idx), ptr + *n, end_n) == -1)
            return -1;
        *n += end_n + strlen(DELIM_END(delim_idx));
    } else {
        if (add_node(head, DELIM_ID(delim_idx), ptr, *n) == -1)
            return -1;
    }
    return 0;
}

static int add_token_node(struct token_node *head, char *ptr,
                            size_t delim_idx, size_t *n)
{
    if (*n) {
        if (add_node(head, ID_TEXT, ptr, *n) == -1)
            return delete_token_node_list(head), -1;
    } else {
        (*n) += strlen(DELIM_STR(delim_idx));
        if (DELIM_TYPE(delim_idx) == T_WITHOUT)
            return 0;
        if (analyse_delimiter(head, ptr, delim_idx, n) == -1)
            return -1;
    }
    return 0;
}

static struct token_node *create_token_list_head(void)
{
    struct token_node *head = malloc(sizeof(struct token_node));

    if (!head)
        return NULL;
    head->content = NULL;
    head->id = ID_TEXT;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

struct token_node *create_token_list_from_line(char *line)
{
    struct token_node *head = create_token_list_head();
    size_t delim_idx;
    size_t i = 0;

    while (line[i]) {
        delim_idx = get_delim_index(line + i);
        while (line[i] && DELIM_ID(delim_idx) == ID_TEXT)
            delim_idx = get_delim_index(line + ++i);
        if (add_token_node(head, line, delim_idx, &i) == -1)
            return NULL;
        line += i;
        i = 0;
    }
    return head;
}
