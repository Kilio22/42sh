/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** display_map
*/

#include <ncurses.h>
#include <stdlib.h>
#include "snake.h"
#include "my_string.h"
#include "my.h"

static int print_description(game_t *snake)
{
    if (mvprintw(LINE_HSCORE + 2, COL_HSCORE, "Up:              Z") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE + 4, COL_HSCORE, "Left:            Q") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE + 6, COL_HSCORE, "Down:            S") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE + 8, COL_HSCORE, "Right:           D") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE + 10, COL_HSCORE, "Pause:           P") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE + 12, COL_HSCORE, "Quit:            E") == ERR)
        return 1;
    if (snake->start == 1) {
        if (mvprintw(11, 38, "Press P to start")
== ERR)
            return 1;
    }
    return 0;
}

static int print_score(game_t *snake)
{
    char *score = my_itoa(snake->score);
    char *highs = my_itoa(snake->highscore);

    if (score == NULL)
        return 1;
    if (mvprintw(LINE_SNAKE, COL_SNAKE, "SNAKE GAME") == ERR)
        return 1;
    if (mvprintw(LINE_SCORE, COL_SCORE, "Score: ") == ERR)
        return 1;
    if (mvprintw(LINE_SCORE, COL_SCORE + 18 - my_strlen(score), score) == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE, COL_HSCORE, "Highscore: ") == ERR)
        return 1;
    if (mvprintw(LINE_HSCORE, COL_HSCORE + 18 - my_strlen(highs), highs) == ERR)
        return 1;
    free(score);
    free(highs);
    return 0;
}

static int print_line(game_t *snake, int lines)
{
    for (int col = 0; col < NB_COLS; col++) {
        if (attron(COLOR_PAIR(snake->map[lines][col])) == ERR)
            return 1;
        if (mvprintw(lines, col, " ") == ERR)
            return 1;
        if (attroff(COLOR_PAIR(snake->map[lines][col])) == ERR)
            return 1;
    }
    return 0;
}

int print_map(game_t *snake)
{
    for (int lines = 0; lines < NB_LINES; lines++) {
        if (print_line(snake, lines) == 1)
            return 1;
    }
    if (print_score(snake) == 1)
        return 1;
    if (snake->score == 0 && snake->start == 0) {
        snake->start++;
        snake->pause = true;
    }
    if (print_description(snake) == 1)
        return 1;
    return 0;
}