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

int analyse_exit_status(int wstatus)
{
    int signal_index;

    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus))
        signal_index = WTERMSIG(wstatus) - 1;
    if (WIFSTOPPED(wstatus))
        signal_index = WSTOPSIG(wstatus) - 1;
    if (signal_index < 0 || signal_index > 32)
        return fputs("Unknown signal caught.\n", stderr), 1;
    fputs(constants_sig[signal_index], stderr);
    if (WCOREDUMP(wstatus))
        fputs(" (core dumped)", stderr);
    fputc('\n', stderr);
    return (signal_index + 129);
}

static pid_t get_pid_of_last(struct pipe_s *p)
{
    while (p->next)
        p = p->next;
    return p->pid;
}

ret_t get_command_status(struct my_shell *shell, struct pipe_s *p, pid_t pgid)
{
    ret_t ret;
    int wstatus;
    pid_t pid_of_last = get_pid_of_last(p);

    if (is_builtin(p->token_list->content) && !p->next)
        return pgid;
    set_foreground_pgrp(pgid);
    if (waitpid(pid_of_last, &wstatus, 0) == -1)
        return -1;
    ret = analyse_exit_status(wstatus);
    killpg(pgid, SIGKILL);
    set_foreground_pgrp(shell->pgid);
    return ret;
}
