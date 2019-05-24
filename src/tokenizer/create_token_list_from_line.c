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

static size_t find_next_delim_index(char *line)
{
    size_t i = 0;
    size_t delim = get_delim_index(line);

    while (line[i]) {
        // if (DELIM_ID(delim) == ID_SQUOTES || DELIM_ID(delim) == ID_DQUOTES) {

        // }
        if (DELIM_TYPE(delim) == T_INHIBITOR) {
            RM_CHAR(line, i);
            delim = get_delim_index(line + ++i);
            continue;
        }
        if (DELIM_ID(delim) != ID_TEXT)
            break;
        delim = get_delim_index(line + ++i);
    }
    return i;
}

struct token_node *create_token_list_from_line(char *line)
{
    struct token_node *head = create_token_list_head();
    size_t i = 0;

    if (!head)
        return NULL;
    while (*line) {
        i = find_next_delim_index(line);
        // if (i == -1)
        //     return NULL;
        if (add_token_node(head, line, get_delim_index(line + i), &i) == -1)
            return NULL;
        line += i;
        i = 0;
    }
    if (check_syntax(head) == -1)
        return NULL;
    return head;
}


/*

echo "\"oui"\" == echo "\" + oui + "\" = \oui\
* les dans les guillemets sont pas effectifs

*/
