/*
** EPITECH PROJECT, 2019
** history
** File description:
** init_history
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "history.h"
#include "my_string.h"
#include "my.h"

static void fill_content(breakpoints_t *historic, history_t *content,
char *time, char *str)
{
    static int number = 1;
    time_t timer;

    if (my_str_isnum(time, false) == false)
        return;
    timer = strtol(time, NULL, 10);
    content->content->number = number;
    content->content->timer = timer;
    content->content->command = my_strdup(str);
    content->next = NULL;
    content->old = historic->last;
    if (historic->last != NULL)
        historic->last->next = content;
    historic->last = content;
    if (historic->head == NULL)
        historic->head = content;
    number++;
}

static int read_history(breakpoints_t *historic, FILE *stream)
{
    char *time = get_line(stream);
    char *str = get_line(stream);
    history_t *content;

    while (time != NULL && str != NULL) {
        content = malloc(sizeof(history_t));
        if (content == NULL)
            return -1;
        content->content = malloc(sizeof(content_t));
        if (content->content == NULL)
            return -1;
        fill_content(historic, content, time, str);
        free(time);
        free(str);
        time = get_line(stream);
        str = get_line(stream);
    }
    free(time);
    free(str);
    return 0;
}

static int empty_history(breakpoints_t *historic)
{
    history_t *content = malloc(sizeof(history_t));
    time_t timer;

    if (content == NULL)
        return -1;
    content->next = NULL;
    content->old = NULL;
    content->content = malloc(sizeof(content_t));
    if (content->content == NULL)
        return -1;
    content->content->command = my_strdup("./42sh");
    if (content->content->command == NULL)
        return -1;
    content->content->number = 0;
    content->content->timer = time(&timer);
    historic->head = content;
    historic->last = content;
    return 0;
}

int init_history(breakpoints_t *historic)
{
    FILE *stream = fopen(".history", "r");
    time_t timer = time(&timer);
    int ret_val = 0;

    historic->head = NULL;
    historic->last = NULL;
    if (stream == NULL) {
        ret_val = empty_history(historic);
        return ret_val;
    } else {
        ret_val = read_history(historic, stream);
        if (historic->head == NULL)
            ret_val = empty_history(historic);
    }
    fclose(stream);
    return ret_val;
}