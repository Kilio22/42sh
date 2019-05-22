/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "history.h"
#include "my_stdio.h"
#include "my_string.h"
#include "my.h"

static void print_history(breakpoints_t *historic)
{
    history_t *current = historic->head;
    struct tm *timer;

    while (current != NULL) {
        timer = localtime(&(current->content->timer));
        if (timer == NULL)
            continue;
        my_printf("%d\t", current->content->number);
        if (timer->tm_hour < 10)
            my_putchar('0');
        my_printf("%d:", timer->tm_hour);
        if (timer->tm_min < 10)
            my_putchar('0');
        my_printf("%d\t%s\n", timer->tm_min, current->content->command);
        current = current->next;
    }
}

int history(breakpoints_t *historic)
{
    char *buff;
    char *str;

    while (1) {
        buff = get_line(stdin);
        if (buff == NULL)
            continue;
        if (my_strcmp("quit", buff) == 0)
            break;
        if (my_strncmp("!", buff, 1) == 0) {
            str = find_history(historic, buff);
            if (str != NULL) {
                fprintf(stderr, "%s\n", str);
                add_history(str, historic);
                free(str);
            }
            free(buff);
            continue;
        }
        if (add_history(buff, historic) == -1)
            return -1;
        if (my_strcmp("history", buff) == 0)
            print_history(historic);
        free(buff);
    }
    free(buff);
    return 0;
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
    if (save_history(historic) == -1)
        ret_val = 84;
    free_history(historic);
    free(historic);
    return ret_val;
}
