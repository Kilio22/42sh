/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <stdlib.h>
#include <time.h>
#include "shell.h"

int main(int argc, char const *argv[], char const *env[])
{
    struct my_shell *shell;

    if (argc > 1)
        fprintf(stderr, "%s doesn't take any arguments.\n", argv[0]);
    shell = create_my_shell(env);
    if (!shell)
        return 84;
    srand(time(NULL));
    return loop_shell(shell);
}
