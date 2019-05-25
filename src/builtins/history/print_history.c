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
#include "shell.h"

int print_history(struct my_shell *shell, char **av __attribute__((unused)))
{
    struct history_s *current = shell->history->head;
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
    return 0;
}