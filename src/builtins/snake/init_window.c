/*
** EPITECH PROJECT, 2019
** snake
** File description:
** init_window
*/

#include <sys/ioctl.h>
#include <termios.h>
#include <ncurses.h>

int set_term_mode(int i)
{
    static struct termios oldT;
    static struct termios newT;

    if (i == 0) {
        if (ioctl(0, TCGETS, &oldT) == -1)
            return 1;
        if (ioctl(0, TCGETS, &newT) == -1)
            return 1;
        newT.c_lflag &= ~ECHO;
        newT.c_lflag &= ~ICANON;
        newT.c_cc[VMIN] = 0;
        newT.c_cc[VTIME] = 2;
        if (ioctl(0, TCSETS, &newT) == -1)
            return 1;
    }
    if (i == 1)
        if (ioctl(0, TCSETS, &oldT) == -1)
            return 1;
    return 0;
}

int init_colors(void)
{
    if (init_pair(1, COLOR_BLACK, COLOR_BLACK) == ERR)
        return 1;
    if (init_pair(2, COLOR_RED, COLOR_RED) == ERR)
        return 1;
    if (init_pair(3, COLOR_BLUE, COLOR_BLUE) == ERR)
        return 1;
    if (init_pair(4, COLOR_BLUE, COLOR_CYAN) == ERR)
        return 1;
    if (init_pair(5, COLOR_GREEN, COLOR_GREEN) == ERR)
        return 1;
    if (init_pair(6, COLOR_YELLOW, COLOR_YELLOW) == ERR)
        return 1;
    return 0;
}

int init_window(void)
{
    initscr();
    if (start_color() == ERR)
        return 1;
    if (keypad(stdscr, TRUE) == ERR)
        return 1;
    if (curs_set(0) == ERR)
        return 1;
    if (set_term_mode(0) == 1)
        return 1;
    if (init_colors() == 1)
        return 1;
    return 0;
}

int close_window(int err_code)
{
    int ret_val = err_code;

    if (curs_set(1) == ERR)
        ret_val = 1;
    if (set_term_mode(1) == 1)
        ret_val = 1;
    if (clear() == ERR)
        ret_val = 1;
    if (endwin() == ERR)
        ret_val = 1;
    return ret_val;
}