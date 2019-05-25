/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** check_command
*/

#include "my_stdio.h"
#include "my_string.h"
#include "minishell.h"

static int check_pipe_arguments(char **command, size_t i, bool has_out)
{
    if (has_out)
        return DISPLAY_RETURN("Ambiguous output redirect.", 0);
    if (i == 0)
        return DISPLAY_RETURN("Invalid null command.", 0);
    if (!command[i + 1])
        return DISPLAY_RETURN("Invalid null command.", 0);
    if (my_strchr((char *) CHAR_WORDS, *command[i - 1]))
        return DISPLAY_RETURN("Invalid null command.", 0);
    if (my_strchr((char *) CHAR_WORDS, *command[i + 1]))
        return DISPLAY_RETURN("Invalid null command.", 0);
    return 1;
}

static int check_redirection_arguments(char **command, int i, bool has_fd,
                                        int pipe_nb)
{
    char *out = "Ambiguous input redirect.";

    if (*command[i] == '>')
        out = "Ambiguous output redirect.";
    if (has_fd)
        return DISPLAY_RETURN(out, 0);
    if (pipe_nb != 0 && *command[i] == '<')
        return DISPLAY_RETURN(out, 0);
    if (!command[i + 1])
        return DISPLAY_RETURN(out, 0);
    if (my_strchr((char *) CHAR_WORDS, *command[i + 1]))
        return DISPLAY_RETURN(out, 0);
    return 1;
}

static int check_command_syntax(char **command)
{
    int props[3] = {false, false, 0};
    int n_var = 1;

    for (size_t i = 0; command[i]; i++) {
        if (*command[i] == '<') {
            n_var = check_redirection_arguments(command, i, props[0], props[2]);
            props[0] = true;
        } else if (*command[i] == '>') {
            n_var = check_redirection_arguments(command, i, props[1], props[2]);
            props[1] = true;
        }
        if (*command[i] == '|') {
            n_var = check_pipe_arguments(command, i, props[1]);
            props[2] += 1;
        }
        if (!n_var)
            return -1;
    }
    return 0;
}

bool check_if_commands_syntax_valid(char ***commands)
{
    for (size_t i = 0; commands[i]; i++) {
        if (check_command_syntax(commands[i]) == -1)
            return false;
    }
    return true;
}
