/*
** EPITECH PROJECT, 2019
** history
** File description:
** replace_string_history
*/

#include <stdlib.h>
#include <string.h>
#include <my_string.h>
#include "history.h"

static char *my_strcat_freeleft(const char *left, const char *right)
{
    size_t len = my_strlen(left);
    char *new = malloc(len + my_strlen(right) + 1);

    if (!left || !right || !new)
        return (NULL);
    my_strcpy(new, left);
    my_strcpy(&new[len], right);
    free((char *) left);
    return (new);
}

static char *error_and_return(char *flag, char *end)
{
    char *new_str = my_strndup(flag, end - flag);

    fprintf(stderr, "!%s: Event not found\n", new_str);
    free(new_str);
    return NULL;
}

static char *check_flag(breakpoints_t *historic, char *flag, char **str_global)
{
    char *end;
    char *end1;
    char *end2;
    char *str;

    if (flag[1] == '!') {
        *str_global = my_strcat(*str_global,
my_strdup(historic->last->content->command));
        if (str_global == NULL)
            return NULL;
        return flag + 2;
    } else {
        end1 = my_strchrnul(flag, ' ');
        end2 = my_strchrnul(flag, '\t');
        end = (end2 < end1) ? end2 : end1;
        str = find_history(historic, my_strndup(flag, end - flag));
        if (str == NULL)
            return error_and_return(flag, end);
        *str_global = my_strcat(*str_global, str);
        return end;
    }
}

int replace_str_history(struct token_node *node, breakpoints_t *historic)
{
    char *str_global = my_strdup("");
    char *begin = node->content;
    char *flag = strchr(begin, '!');
    char *ret_str;

    if (str_global == NULL)
        return -1;
    while (flag) {
        str_global = my_strcat(str_global, my_strndup(begin, flag - begin));
        ret_str = check_flag(historic, flag, &str_global);
        if (ret_str == NULL)
            return -1;
        begin = ret_str;
        flag = strchr(begin, '!');
    }
    str_global = my_strcat_freeleft(str_global, begin);
    free(node->content);
    node->content = str_global;
    return 0;
}