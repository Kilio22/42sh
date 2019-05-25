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
#include "shell.h"
#include "my_string.h"
#include "my.h"

static char *command_number(struct breakpoints_s *historic, int number)
{
    struct history_s *current = historic->head;

    while (current->content->number != number)
        current = current->next;
    return my_strdup(current->content->command);
}

static char *command_str(struct breakpoints_s *historic, char *str)
{
    struct history_s *current = historic->last;

    while (current != NULL && my_strncmp(current->content->command,
str, my_strlen(str)) != 0)
        current = current->old;
    if (current == NULL)
        return NULL;
    return my_strdup(current->content->command);
}

char *find_history(struct breakpoints_s *historic, char *buff)
{
    int number;
    char *str = my_strdup(buff + 1);
    char *ret_str;

    if (my_strlen(buff) < 2)
        return NULL;
    free(buff);
    if (my_str_isnum(str, false) == true) {
        number = my_atoi(str);
        free(str);
        if (number > historic->last->content->number)
            return NULL;
        return command_number(historic, number);
    }
    ret_str = command_str(historic, str);
    free(str);
    return ret_str;
}