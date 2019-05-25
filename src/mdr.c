/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** mdr
*/

#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

void signal_ign(bool mdr)
{
	signal(SIGQUIT, (mdr) ? SIG_IGN : SIG_DFL);
	if (isatty(STDIN_FILENO)) {
		signal(SIGINT, (mdr) ? SIG_IGN : SIG_DFL);
		signal(SIGTSTP, (mdr) ? SIG_IGN : SIG_DFL);
		signal(SIGTTIN, (mdr) ? SIG_IGN : SIG_DFL);
		signal(SIGTTOU, (mdr) ? SIG_IGN : SIG_DFL);
		signal(SIGTERM, (mdr) ? SIG_IGN : SIG_DFL);
	}
}
