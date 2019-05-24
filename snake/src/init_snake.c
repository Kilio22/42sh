/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** init_snake
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "snake.h"
#include "my_string.h"
#include "my_stdio.h"
#include "my.h"

void init_snake(game_t *snake)
{
    int x = 31;
    int y = 4;

    for (int i = 0; i < 3; i++) {
        snake->body[i].direction = RIGHT;
        snake->body[i].x = x;
        snake->body[i].y = y;
        x--;
    }
    for (int i = 3; i < 800; i++)
        snake->body[i].direction = -1;
}

game_t init_game(void)
{
    game_t snake;

    snake.direction = RIGHT;
    snake.pause = false;
    snake.loose = false;
    snake.score = 0;
    snake.start = 0;
    snake.first[0] = 31;
    snake.first[1] = 4;
    snake.last[0] = 29;
    snake.last[1] = 4;
    for (int i = 0; i < NB_LINES; i++) {
        for (int j = 0; j < NB_COLS; j++)
            snake.map[i][j] = map_snake[i][j];
    }
    snake.highscore = init_highscore();
    init_snake(&snake);
    return snake;
}

void save_snake(game_t *snake)
{
    int fd = open("highscore.txt", O_CREAT | O_RDWR | O_TRUNC,
S_IRUSR | S_IWUSR);
    char *highscore = my_itoa(snake->highscore);

    if (fd == -1)
        return;
    if (highscore == NULL)
        return;
    write(fd, highscore, my_strlen(highscore));
    free(highscore);
}

int init_highscore(void)
{
    int fd = open("highscore.txt", O_RDONLY);
    int ret_val = 0;
    char *buff;

    if (fd == -1)
        return 0;
    buff = get_next_line(fd);
    if (buff == NULL)
        return 0;
    if (my_str_isnum(buff, 0) == true)
        ret_val = my_atoi(buff);
    free(buff);
    return ret_val;
}