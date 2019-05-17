/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "history.h"
#include "my_stdio.h"
#include "my_string.h"

void print_history(history_t *historic)
{
    history_t *current = historic;

    while (current != NULL) {
        my_printf("%d  %d:%d   %s\n", historic->content->number,
historic->content->hour->tm_hour, historic->content->hour->tm_min,
historic->content->command);
        current = current->next;
    }
}

void history(history_t *historic)
{
    //time_t timer;
    char *buff;

    while (1) {
        buff = get_line(stdin);
        if (buff == NULL)
            continue;
        if (my_strcmp("history", buff) == 0)
            print_history(historic);
        if (my_strcmp("quit", buff) == 0)
            break;
        free(buff);
    }
    free(buff);
}

int init_history(history_t *historic)
{
    time_t timer;

    historic->old = NULL;
    historic->next = NULL;
    historic->content = malloc(sizeof(content_t));
    if (historic->content == NULL)
        return -1;
    historic->content->number = 0;
    if (time(&timer) == -1)
        return -1;
    historic->content->hour = localtime(&timer);
    if (historic->content->hour == NULL)
        return -1;
    historic->content->command = my_strdup("./42sh");
    if (historic->content->command == NULL)
        return -1;
    return 0;
}

void free_history(history_t *historic)
{
    while (historic != NULL) {
        free(historic->content->command);
        free(historic->content);
        historic = historic->next;
    }
}

int main(void)
{
    history_t *historic = malloc(sizeof(history_t));

    if (historic == NULL)
        return 84;
    if (init_history(historic) == -1)
        return 84;
    history(historic);
    free_history(historic);
    free(historic);
    return (0);
}
