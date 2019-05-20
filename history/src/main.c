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
#include "my.h"

void print_history(breakpoints_t *historic)
{
    history_t *current = historic->start;
    struct tm *timer;

    while (current != NULL) {
        timer = localtime(&(current->content->timer));
        if (timer == NULL)
            continue;
        my_printf("%d  %d:%d   %s\n", current->content->number,
timer->tm_hour, timer->tm_min, current->content->command);
        current = current->next;
    }
}

char *my_ltoa(long int nb)
{
    char str[50] = {0};
    int isneg = (nb < 0) ? 1 : 0;
    int r;
    int i = 0;

    if (nb == -2147483648)
        return (my_strdup("-2147483648"));
    nb = (nb < 0) ? -nb : nb;
    do {
        r = nb % 10;
        nb /= 10;
        str[i++] = r + '0';
    } while (nb);
    if (isneg)
        str[i++] = '-';
    str[i] = '\0';
    return (my_strdup(my_revstr(str)));
}

int add_history(char *buff, breakpoints_t *historic)
{
    history_t *new_historic = malloc(sizeof(history_t));

    if (new_historic == NULL)
        return -1;
    new_historic->content = malloc(sizeof(content_t));
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

int history(breakpoints_t *historic)
{
    char *buff;

    while (1) {
        buff = get_line(stdin);
        if (buff == NULL)
            continue;
        if (my_strcmp("history", buff) == 0)
            print_history(historic);
        if (my_strcmp("quit", buff) == 0)
            break;
        if (add_history(buff, historic) == -1)
            return -1;
        free(buff);
    }
    free(buff);
    return 0;
}

int init_history(breakpoints_t *historic)
{
    historic->start = malloc(sizeof(history_t));
    if (historic->start == NULL)
        return -1;
    historic->start->old = NULL;
    historic->start->next = NULL;
    historic->start->content = malloc(sizeof(content_t));
    if (historic->start->content == NULL)
        return -1;
    historic->start->content->number = 0;
    if (time(&(historic->start->content->timer)) == -1)
        return -1;
    historic->start->content->command = my_strdup("./42sh");
    if (historic->start->content->command == NULL)
        return -1;
    historic->last = historic->start;
    return 0;
}

void free_history(breakpoints_t *historic)
{
    history_t *next = historic->start->next;

    while (historic->start != NULL) {
        free(historic->start->content->command);
        free(historic->start->content);
        free(historic->start);
        historic->start = next;
        if (next != NULL)
            next = historic->start->next;
    }
}

void save_history(breakpoints_t *historic)
{
    int fd = open()
}

int main(void)
{
    int ret_val = 0;
    breakpoints_t *historic = malloc(sizeof(breakpoints_t));

    if (historic == NULL)
        return 84;
    if (init_history(historic) == -1)
        return 84;
    if (history(historic) == -1)
        ret_val = 84;
    save_history(historic);
    free_history(historic);
    free(historic);
    return ret_val;
}
