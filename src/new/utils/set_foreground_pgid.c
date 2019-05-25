/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set_foreground_pgid
*/

#include <sys/types.h>
#include <unistd.h>

int set_foreground_pgid(pid_t pgid)
{
    if (!isatty(STDIN_FILENO))
        return 0;
    if (tcsetpgrp(STDIN_FILENO, pgid) == -1)
        return -1;
    if (tcsetpgrp(STDOUT_FILENO, pgid) == -1)
        return -1;
    if (tcsetpgrp(STDERR_FILENO, pgid) == -1)
        return -1;
    return 0;
}
