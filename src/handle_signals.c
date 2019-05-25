/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** mdr
*/

#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

void ignore_signals(bool flag)
{
    if (!isatty(STDIN_FILENO))
        return;
    if (flag == true) {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
    } else {
        signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTERM, SIG_DFL);
    }
}
