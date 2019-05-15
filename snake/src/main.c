/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_string.h"
#include "my_stdio.h"
#include "my.h"
#include "snake.h"

static int check_event(char *buff, game_t *snake)
{
    int ret_val = 0;

    for (int i = 0; i < 6; i++) {
        if (my_strncmp(buff, controls[i], 1) == 0)
            ret_val = i + 1;
    }
    if (ret_val == PAUSE)
        snake->pause = (snake->pause == true) ? false : true;
    if (ret_val == QUIT)
        return 1;
    if ((ret_val == UP && snake->direction != DOWN)
|| (ret_val == LEFT && snake->direction != RIGHT) || (ret_val == DOWN
&& snake->direction != UP) || (ret_val == RIGHT && snake->direction != LEFT))
        snake->direction = ret_val;
    return 0;
}

static void check_size_window(void)
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

static int print_description(void)
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

static int print_map(game_t *snake)
{
    for (int lines = 0; lines < NB_LINES; lines++) {
        if (print_line(snake, lines) == 1)
            return 1;
    }
    if (print_score(snake) == 1)
        return 1;
    if (print_description() == 1)
        return 1;
    return 0;
}

void update_last(game_t *snake)
{
    int x = snake->last[0];
    int y = snake->last[1];
    int new_x = snake->last[0];
    int new_y = snake->last[1];

    new_y = (snake->map[y - 1][x] == 3) ? y - 1 : new_y;
    new_y = (snake->map[y + 1][x] == 3) ? y + 1 : new_y;
    new_x = (snake->map[y][x - 1] == 3) ? x - 1: new_x;
    new_x = (snake->map[y][x + 1] == 3) ? x + 1: new_x;
    snake->map[y][x] = 1;
    snake->last[0] = new_x;
    snake->last[1] = new_y;
}

void generate_new_fruit(game_t *snake, int new_x, int new_y)
{
    int ret_val = 1;
    int x;
    int y;
    int color = rand() % 10;

    while (ret_val != 0) {
        x = START_MAP_X + (rand() % 40);
        y = START_MAP_Y + (rand() % 20);
        if (x == new_x && y == new_y)
            continue;
        if (snake->map[y][x] == 3 || snake->map[y][x] == 4)
            continue;
        ret_val = 0;
        snake->map[y][x] = (color < 3) ? 6 : 5;
    }
}

void update_new(game_t *snake, int new_x, int new_y)
{
    if (snake->map[new_y][new_x] == 3)
        snake->loose = true;
    if (snake->map[new_y][new_x] == 5 || snake->map[new_y][new_x] == 6) {
        snake->score = (snake->map[new_y][new_x] == 5) ?
snake->score + 1 : snake->score + 2;
        snake->highscore = (snake->score > snake->highscore) ?
snake->score : snake->highscore;
        generate_new_fruit(snake, new_x, new_y);
    }
    snake->map[snake->first[1]][snake->first[0]] = 3;
    snake->map[new_y][new_x] = 4;
    snake->first[0] = new_x;
    snake->first[1] = new_y;
}

void update_snake(game_t *snake)
{
    int new_x = snake->first[0];
    int new_y = snake->first[1];

    if (snake->direction == UP)
        new_y--;
    if (snake->direction == LEFT)
        new_x--;
    if (snake->direction == DOWN)
        new_y++;
    if (snake->direction == RIGHT)
        new_x++;
    if (new_x < START_MAP_X || new_x > END_MAP_X
|| new_y < START_MAP_Y || new_y > END_MAP_Y) {
        snake->loose = true;
        return;
    }
    update_last(snake);
    update_new(snake, new_x, new_y);
}

int read_input(game_t *snake)
{
    int ret_val = 0;
    char buff[20];

    if (read(0, buff, 20) != 0) {
        ret_val = check_event(buff, snake);
        for (int i = 0; i < 20; i++)
            buff[i] = '\0';
    }
    return ret_val;
}

int window_loop(game_t *snake)
{
    int ret_val = 0;

    if (init_window() == 1)
        return close_window(1);
    while (1) {
        check_size_window();
        clear();
        ret_val = read_input(snake);
        if (ret_val == 1 || snake->loose == true)
            break;
        if (snake->pause == true)
            continue;
        update_snake(snake);
        if (print_map(snake) == 1)
            return close_window(1);
        refresh();
    }
    return close_window(0);
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

game_t init_game(void)
{
    game_t snake;

    snake.direction = RIGHT;
    snake.pause = false;
    snake.loose = false;
    snake.score = 0;
    snake.first[0] = 31;
    snake.first[1] = 4;
    snake.last[0] = 29;
    snake.last[1] = 4;
    for (int i = 0; i < NB_LINES; i++) {
        for (int j = 0; j < NB_COLS; j++)
            snake.map[i][j] = map_snake[i][j];
    }
    snake.highscore = init_highscore();
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

int main(void)
{
    int ret_val;

    game_t snake = init_game();
    ret_val = window_loop(&snake);
    save_snake(&snake);
    return (ret_val == 1) ? 84 : 0;
}
