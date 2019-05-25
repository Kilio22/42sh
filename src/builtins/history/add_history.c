/*
** EPITECH PROJECT, 2019
** history
** File description:
** add_history
*/

#include <stdlib.h>
#include "history.h"
#include "my_string.h"
#include "shell.h"

static int is_in_history(char *buff, struct breakpoints_s *historic)
{
    struct history_s *current = historic->head;

    while (current != NULL) {
        if (my_strcmp(buff, current->content->command) == 0)
            return 0;
        current = current->next;
    }
    return -1;
}

static int change_history(char *buff, struct breakpoints_s *historic)
{
    struct history_s *head = historic->head;
    time_t timer = time(&timer);

    while (historic->head != NULL) {
        if (my_strcmp(buff, historic->head->content->command) == 0)
            break;
        historic->head = historic->head->next;
    }
    historic->head->content->timer = timer;
    historic->head->content->number = historic->last->content->number + 1;
    if (historic->head->old != NULL && historic->head->next != NULL)
        historic->head->old->next = historic->head->next;
    if (historic->head->next != NULL && historic->head->old != NULL)
        historic->head->next->old = historic->head->old;
    if (historic->head->next != NULL)
        historic->last->next = historic->head;
    historic->head->old = historic->last;
    historic->head->next = NULL;
    historic->last = historic->head;
    historic->head = head;
    return 0;
}

int add_history(char *buff, struct breakpoints_s *historic)
{
    struct history_s *new_historic;

    if (is_in_history(buff, historic) == 0)
        return change_history(buff, historic);
    new_historic = malloc(sizeof(struct history_s));
    if (new_historic == NULL)
        return -1;
    new_historic->content = malloc(sizeof(struct content_s));
    if (new_historic->content == NULL)
        return -1;
    if (time(&(new_historic->content->timer)) == -1)
        return -1;
    new_historic->content->command = my_strdup(buff);
    if (new_historic->content->command == NULL)
        return -1;
    new_historic->content->number = historic->last->content->number + 1;
    historic->last->next = new_historic;
    new_historic->next = NULL;
    new_historic->old = historic->last;
    historic->last = new_historic;
    return 0;
}