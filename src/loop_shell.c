/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** loop_shell
*/

#include <stdlib.h>
#include "shell.h"

static char *get_prompt(void)
{
    return get_line(stdin);
}

int loop_shell(struct my_shell *shell)
{
    char *prompt;

    while (true) {
        prompt = get_prompt();
        if (!prompt)
            return 84;
        if (execute_line(shell, prompt) == -1)
            return 84;
    }
    return 0;
}
