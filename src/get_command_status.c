/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** get_command_status
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

static int analyse_exit_status(int wstatus)
{
    int signal_index;

    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus))
        signal_index = WTERMSIG(wstatus) - 1;
    if (WIFSTOPPED(wstatus))
        signal_index = WSTOPSIG(wstatus) - 1;
    if (signal_index < 0 || signal_index > 32)
        return fputs("Unknown signal caught.\n", stderr), 0;
    fputs(constants_sig[signal_index], stderr);
    if (WCOREDUMP(wstatus))
        fputs(" (core dumped)", stderr);
    fputc('\n', stderr);
    return (signal_index + 129);
}

ret_t get_command_status(struct my_shell *shell, struct pipe_s *p, pid_t pgid)
{
    ret_t n_return;
    int wstatus;

    if (is_builtin(p->token_list->content) && !p->next)
        return shell->n_return;
    set_foreground_pgrp(pgid);
    if (waitpid(pgid, &wstatus, WUNTRACED) == -1)
        return -1;
    n_return = analyse_exit_status(wstatus);
    killpg(pgid, SIGKILL);
    set_foreground_pgrp(shell->pgid);
    return n_return;
}
