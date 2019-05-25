/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** loop_shell
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

static char *get_prompt(void)
{
    char *line;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ > ", 4);
    line = get_line(stdin);
    return line;
}

int loop_shell(struct my_shell *shell)
{
    char *prompt;
    ret_t n_return = 0;

    ignore_signals(true);
    while (true) {
        prompt = get_prompt();
        if (!prompt)
            break;
        execute_line(shell, prompt);
        free(prompt);
    }
    n_return = shell->n_return;
    free_alias(shell->aliases);
    free_history(shell->history);
    destroy_my_shell(shell);
    if (isatty(STDIN_FILENO))
        puts("exit");
    return n_return;
}
