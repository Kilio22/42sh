/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** create_token_list_from_line
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "tokenizer.h"

static ssize_t get_container_end(char *ptr, char *begin, char *end)
{
    size_t count = 1;

    for (ssize_t i = 0; ptr[i]; i++) {
        if (begin && !strncmp(ptr + i, begin, strlen(begin)))
            ++count;
        if (!strncmp(ptr + i, end, strlen(end)))
            --count;
        if (count == 0)
            return i;
    }
    fprintf(stderr, "Unmatched '%s'\n", end);
    return -1;
}

static int analyse_delimiter(struct token_node *head, char *ptr,
                                size_t d, ssize_t *n)
{
    ssize_t end_n;

    if (DELIM_TYPE(d) == T_CONTAINER) {
        end_n = get_container_end(ptr + *n, DELIM_STR(d), DELIM_END(d));
        if (end_n == -1)
            return -1;
        if (add_node(head, DELIM_ID(d), ptr + *n, end_n) == -1)
            return -1;
        *n += end_n + strlen(DELIM_END(d));
    } else {
        if (add_node(head, DELIM_ID(d), ptr, *n) == -1)
            return -1;
    }
    return 0;
}

static int add_token_node(struct token_node *head, char *ptr,
                            size_t delim_idx, ssize_t *n)
{
    if (*n) {
        if (add_node(head, ID_TEXT, ptr, *n) == -1)
            return delete_token_node_list(head), -1;
    } else {
        if (!DELIM_STR(delim_idx))
            return 0;
        (*n) += strlen(DELIM_STR(delim_idx));
        if (DELIM_TYPE(delim_idx) == T_WITHOUT)
            return 0;
        if (analyse_delimiter(head, ptr, delim_idx, n) == -1)
            return -1;
    }
    return 0;
}

static ssize_t find_next_delim_index(char *line)
{
    ssize_t i = 0;
    ssize_t i_end;
    size_t d = get_delim_index(line);

    while (line[i]) {
        if (DELIM_TYPE(d) == T_CONTAINER && DELIM_ID(d) != ID_PARENTHESIS) {
            RM_CHAR(line, i);
            if ((i_end = get_container_end(line + i, NULL, DELIM_END(d))) == -1)
                return -1;
            i += i_end;
            RM_CHAR(line, i);
            d = get_delim_index(line + i);
            continue;
        }
        if (DELIM_TYPE(d) == T_INHIBITOR) {
            RM_CHAR(line, i);
        } else if (DELIM_ID(d) != ID_TEXT)
            break;
        d = get_delim_index(line + ++i);
    }
    return i;
}

struct token_node *create_token_list_from_line(char *line)
{
    struct token_node *head = create_token_list_head();
    ssize_t i = 0;

    if (!head)
        return NULL;
    while (*line) {
        i = find_next_delim_index(line);
        if (i == -1)
            return NULL;
        if (add_token_node(head, line, get_delim_index(line + i), &i) == -1)
            return NULL;
        line += i;
        i = 0;
    }
    if (check_syntax(head) == -1)
        return NULL;
    return head;
}
