/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** set_foreground_pgrp
*/

#include <sys/types.h>
#include <unistd.h>

int set_foreground_pgrp(pid_t pgrp)
{
    if (!isatty(STDIN_FILENO))
        return 0;
    if (tcsetpgrp(STDIN_FILENO, pgrp) == -1)
        return -1;
    if (tcsetpgrp(STDOUT_FILENO, pgrp) == -1)
        return -1;
    if (tcsetpgrp(STDERR_FILENO, pgrp) == -1)
        return -1;
    return 0;
}
