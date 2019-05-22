/*
** EPITECH PROJECT, 2019
** history
** File description:
** find_in_history
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "my_string.h"
#include "my.h"

static char *command_number(breakpoints_t *historic, int number)
{
    history_t *current = historic->head;

    while (current->content->number != number)
        current = current->next;
    return my_strdup(current->content->command);
}

static char *command_str(breakpoints_t *historic, char *str)
{
    history_t *current = historic->head;
    char *new_str;
    char *ret_str;

    if (my_strncmp(str, "!", 1) == 0) {
        new_str = my_strdup(str + 1);
        ret_str = my_strdup(historic->last->content->command);
        ret_str = my_strcat(ret_str, new_str);
        return ret_str;
    }
    while (current != NULL && my_strncmp(current->content->command,
str, my_strlen(str)) != 0)
        current = current->next;
    if (current == NULL)
        return NULL;
    return my_strdup(current->content->command);
}

char *find_history(breakpoints_t *historic, char *buff)
{
    int number;
    char *str = my_strdup(buff + 1);
    char *ret_str;

    if (my_strlen(buff) < 2)
        return NULL;
    if (my_str_isnum(str, false) == true) {
        number = my_atoi(str);
        free(str);
        if (number > historic->last->content->number) {
            fprintf(stderr, "!%d: Event not found\n", number);
            return NULL;
        }
        return command_number(historic, number);
    }
    ret_str = command_str(historic, str);
    free(str);
    return ret_str;
}