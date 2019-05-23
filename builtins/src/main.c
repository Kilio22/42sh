/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** Main function
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_stdio.h"
#include "my_string.h"

const char *my_builtins[][2] = {
    {"cd", "change the current working directory"},
    {"env", "display the env"},
    {"yes", "loop and display y or the args"},
    {"echo", "display the given arguments"},
    {"exit", "exit the shell with the given return value"},
    {"snake", "launch the snake game"},
    {"where", "display all known instances of command."},
    {"which", "display the real command that the shell execute"},
    {"setenv", "set a new env variable or change an existing one"},
    {"history", "display the history of commands"},
    {"builtins", "display all shell built-in"},
    {"unsetenv", "unset one or more env variable(s)"}
};

void display_builtins(void)
{
    for (int i = 0; i < 12; i++) {
        my_printf("%s", my_builtins[i][0]);
        if (my_strlen(my_builtins[i][0]) < 8)
            my_printf("\t");
        my_printf(" :\t%s\n", my_builtins[i][1]);
    }
}

bool is_a_builtin(const char *str)
{
    for (int i = 0; i < 12; i++)
        if (my_strcmp(str, my_builtins[i][0]) == 0)
            return true;
    return false;
}

static int my_varlen(const char *str)
{
    int i = 0;

    while (str[i] != '\0' && str[i] != '=')
        i++;
    return (i);
}

int find_var_index(char *var, char **env)
{
    int len = my_strlen(var);
    int big_len;
    int i;

    for (i = 0; env[i] != 0; i++) {
        big_len = my_varlen(env[i]);
        big_len = (len > big_len) ? len : big_len;
        if (my_strncmp(var, env[i], big_len) == 0)
            return (i);
    }
    return (-1);
}

char *my_strcat_freeleft(const char *left, const char *right)
{
    size_t len = my_strlen(left);
    char *new = malloc(len + my_strlen(right) + 1);

    if (!left || !right || !new)
        return (NULL);
    my_strcpy(new, left);
    my_strcpy(&new[len], right);
    free((char *) left);
    return (new);
}

void free_path(char **path)
{
    for (size_t i = 0; path[i] != NULL; i++)
        free(path[i]);
    free(path);
}

int find_where_path(char *command, char *env[])
{
    char **path = my_str_towordarray(env[find_var_index("PATH", env)], ":");
    char *str = NULL;
    int occ = 0;

    for (size_t i = 0; path[i] != NULL; i++) {
        str = my_strcat_nofree(path[i], "/");
        if (str == NULL)
            continue;
        str = my_strcat_freeleft(str, command);
        if (str == NULL)
            continue;
        if (access(str, F_OK) == 0) {
            puts(str);
            occ++;
        }
        free(str);
    }
    free_path(path);
    return occ;
}

void my_where(int argc, char *argv[], char *env[])
{
    int occ = 0;

    if (argc < 2)
        my_printf("%s: Too few arguments.\n", argv[0]);
    for (size_t i = 1; i < (size_t) argc; i++) {
        if (is_a_builtin(argv[i]) == true) {
            my_printf("%s is a shell built-in\n");
            occ++;
        }
        occ += find_where_path(argv[i], env);
        if (occ == 0)
            my_printf("%s: Command not found.\n", argv[i]);
        occ = 0;
    }
}

void find_which_path(char *command, char *env[])
{
    char **path = my_str_towordarray(env[find_var_index("PATH", env)], ":");
    char *str = NULL;

    for (size_t i = 0; path[i] != NULL; i++) {
        str = my_strcat_nofree(path[i], "/");
        if (str == NULL)
            continue;
        str = my_strcat_freeleft(str, command);
        if (str == NULL)
            continue;
        if (access(str, F_OK) == 0) {
            puts(str);
            free(str);
            return free_path(path);
        }
        free(str);
    }
    free_path(path);
    my_printf("%s: Command not found.\n", command);
}

void my_which(int argc, char *argv[], char *env[])
{
    if (argc < 2)
        my_printf("%s: Too few arguments.\n", argv[0]);
    for (size_t i = 1; i < (size_t) argc; i++) {
        if (is_a_builtin(argv[i]) == true)
            my_printf("%s: shell built-in command.\n");
        else
            find_which_path(argv[i], env);
    }
}

void print_arg_yes(int argc, char *argv[], int i)
{
    printf("%s", argv[i]);
    if (i + 1 < argc)
        printf(" ");
}

void my_yes(int argc, char *argv[])
{
    int i = 1;

    if (argc == 1) {
        while (1)
            printf("y\n");
        return;
    }
    while (1) {
        while (i < argc) {
            print_arg_yes(argc, argv, i);
            i++;
        }
        i = 1;
        printf("\n");
    }    
}

int main(int argc, char *argv[], char *env[])
{
    if (argc < 2)
        return 84;
    if (my_strcmp(argv[1], "builtins") == 0) {
        display_builtins();
    }
    if (my_strcmp(argv[1], "which") == 0) {
        my_which(argc - 1, argv + 1, env);
    }
    if (my_strcmp(argv[1], "where") == 0) {
        my_where(argc - 1, argv + 1, env);
    }
    if (my_strcmp(argv[1], "yes") == 0) {
        my_yes(argc - 1, argv + 1);
    }
}
