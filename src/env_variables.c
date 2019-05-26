/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** env_variables
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "shell.h"

int env_variables_loop(struct token_node *token, struct my_shell *shell)
{
    int n_val = 0;

    if (!token)
        return 0;
    while (token) {
        if (!token->content) {
            token = token->next;
            continue;
        }
        n_val = env_variables_token(token, shell);
        if (n_val != 0)
            return -1;
        token = token->next;
    }
    return 0;
}