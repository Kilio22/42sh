/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** event_management
*/

#include <ncurses.h>
#include <stdlib.h>
#include "snake.h"
#include "my_string.h"

int check_event(char *buff, game_t *snake)
{
    int ret_val = 0;

    for (int i = 0; i < 6; i++) {
        if (my_strncmp(buff, controls[i], 1) == 0)
            ret_val = i + 1;
    }
    if (ret_val == PAUSE) {
        snake->pause = (snake->pause == true) ? false : true;
        snake->start = (snake->start == 1) ? 2 : snake->start;
    }
    if (ret_val == QUIT)
        return 1;
    if ((ret_val == UP && snake->direction != DOWN)
|| (ret_val == LEFT && snake->direction != RIGHT) || (ret_val == DOWN
&& snake->direction != UP) || (ret_val == RIGHT && snake->direction != LEFT))
        snake->direction = ret_val;
    return 0;
}

void check_size_window(void)
{
    int x;
    int y;

    while (COLS < NB_COLS || LINES < NB_LINES) {
        x = LINES / 2;
        y = (COLS - 18) / 2;
        clear();
        mvprintw(x, y, "Window too small!");
        refresh();
    }
}