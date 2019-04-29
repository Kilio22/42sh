/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
    (void) argc;
    (void) argv;
    loop_shell(init_my_env(env));
    return (0);
}
