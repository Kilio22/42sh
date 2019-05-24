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

#define MAX_ALIAS 400

typedef struct alias_s {
    char *name;
    char *command;
} alias_t;

void init_alias(alias_t alias[MAX_ALIAS])
{
    int i = 0;

    for (; i < MAX_ALIAS; i++)
        alias[i].name = NULL;
}

int find_alias(alias_t alias[MAX_ALIAS], char *name)
{
    int i = 0;

    for (; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            return i;
        if (my_strcmp(name, alias[i].name) == 0)
            return i;
    }
    return -1;
}

void unalias_all(alias_t alias[MAX_ALIAS])
{
    for (int i = 0; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            continue;
        free(alias[i].name);
        free(alias[i].command);
        alias[i].name = NULL;
    }
}

int unalias(alias_t alias[MAX_ALIAS], int index)
{
    int last_index = 0;
    char *tmp;

    for (; last_index < 400; last_index++)
        if (alias[last_index].name == NULL)
            break;
    last_index--;
    tmp = alias[last_index].name;
    alias[last_index].name = alias[index].name;
    alias[index].name = tmp;
    tmp = alias[last_index].command;
    alias[last_index].command = alias[index].command;
    alias[index].command = tmp;
    free(alias[last_index].name);
    free(alias[last_index].command);
    alias[last_index].name = NULL;
    return 0;
}

int my_unalias(int ac, char *av[], alias_t alias[MAX_ALIAS])
{
    int alias_ind;

    if (ac == 1) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return -1;
    }
    for (int i = 1; i < ac; i++) {
        if (my_strcmp("*", av[i]) == 0) {
            unalias_all(alias);
            return 0;
        }
        alias_ind = find_alias(alias, av[i]);
        if (alias_ind == -1 || alias[alias_ind].name == NULL)
            continue;
        if (unalias(alias, alias_ind) == -1) {
            fprintf(stderr, "unalias: error.\n");
            return -1;
        }
    }
    return 0;
}

void display_aliases(alias_t alias[MAX_ALIAS])
{
    for (int i = 0; i < MAX_ALIAS; i++) {
        if (alias[i].name == NULL)
            break;
        printf("%s\t%s\n", alias[i].name, alias[i].command);
    }
}

void display_one_alias(alias_t alias[MAX_ALIAS], char *name)
{
    int index = find_alias(alias, name);

    if (index == -1 || alias[index].name == NULL)
        return;
    printf("%s\n", alias[index].command);
}

int full_alias(void)
{
    fprintf(stderr, "alias: Too many aliases.\n");
    return -1;
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

int new_alias(int ac, char *name, char **cmd, alias_t alias[MAX_ALIAS])
{
    char *new_cmd = my_strdup("");
    int index = find_alias(alias, name);

    if (new_cmd == NULL)
        return -1;
    for (int i = 0; i < ac; i++) {
        new_cmd = my_strcat_freeleft(new_cmd, cmd[i]);
        if (new_cmd == NULL)
            return -1;
        if (i + 1 < ac)
            new_cmd = my_strcat_freeleft(new_cmd, " ");
        if (new_cmd == NULL)
            return -1;
    }
    alias[index].name = my_strdup(name);
    alias[index].command = my_strdup(new_cmd);
    if (alias[index].name == NULL || alias[index].command == NULL)
        return -1;
    free(new_cmd);
    return 0;
}

int change_alias(int ac, int index, char **cmd, alias_t alias[MAX_ALIAS])
{
    char *new_cmd = my_strdup("");

    if (new_cmd == NULL)
        return -1;
    for (int i = 0; i < ac; i++) {
        new_cmd = my_strcat_freeleft(new_cmd, cmd[i]);
        if (new_cmd == NULL)
            return -1;
        if (i + 1 < ac)
            new_cmd = my_strcat_freeleft(new_cmd, " ");
        if (new_cmd == NULL)
            return -1;
    }
    free(alias[index].command);
    alias[index].command = my_strdup(new_cmd);
    if (alias[index].command == NULL)
        return -1;
    return 0;
}

int add_alias(int ac, char *name, char **cmd, alias_t alias[MAX_ALIAS])
{
    int index = find_alias(alias, name);

    if (index == -1)
        return full_alias();
    else if (alias[index].name == NULL) {
        return new_alias(ac, name, cmd, alias);
    } else {
        return change_alias(ac, index, cmd, alias);
    }
}

int my_alias(int ac, char *av[], alias_t alias[MAX_ALIAS])
{
    if (ac == 1)
        display_aliases(alias);
    else if (ac == 2) {
        display_one_alias(alias, av[1]);
    } else {
        return add_alias(ac - 2, av[1], av + 2, alias);
    }
    return 0;
}

const char *my_builtins[][2] = {
    {"cd", "change the current working directory"},
    {"env", "displays the env"},
    {"yes", "loop and displays y or the args"},
    {"echo", "displays the given arguments"},
    {"exit", "exit the shell with the given return value"},
    {"alias", "display aliases, or add a new one for a command"},
    {"snake", "launch the snake game"},
    {"where", "displays all known instances of command."},
    {"which", "displays the real command that the shell execute"},
    {"setenv", "set a new env variable or change an existing one"},
    {"whoami", "displays who you are"},
    {"history", "displays the history of commands"},
    {"unalias", "remove one or more aliases"},
    {"builtins", "displays all shell built-in"},
    {"unsetenv", "unset one or more env variable(s)"}
};

void display_builtins(void)
{
    for (int i = 0; i < 15; i++) {
        my_printf("%s", my_builtins[i][0]);
        if (my_strlen(my_builtins[i][0]) < 8)
            my_printf("\t");
        my_printf(" :\t%s\n", my_builtins[i][1]);
    }
}

bool is_a_builtin(const char *str)
{
    for (int i = 0; i < 15; i++)
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

void my_whoami(void)
{
    char *whoami = getlogin();

    if (whoami == NULL)
        return;
    printf("%s\n", whoami);
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
    alias_t alias[MAX_ALIAS];

    init_alias(alias);
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
    if (my_strcmp(argv[1], "whoami") == 0) {
        my_whoami();
    }
    if (my_strcmp(argv[1], "alias") == 0) {
        my_alias(argc - 1, argv + 1, alias);
        my_alias(1, NULL, alias);
        my_unalias(argc - 1, argv + 1, alias);
        my_alias(1, NULL, alias);
    }
    if (my_strcmp(argv[1], "unalias") == 0) {
        my_unalias(argc - 1, argv + 1, alias);
    }
}
