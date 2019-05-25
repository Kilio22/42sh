/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** execute_line
*/

#include <stdlib.h>
#include "shell.h"

static struct cmd_s *get_next_command(struct cmd_s *command, ret_t n_return)
{
    if (!command->next)
        return NULL;
    if ((command->next->id == CMD_AND && n_return != SUCCESS_RETURN) ||
(command->next->id == CMD_OR && n_return == SUCCESS_RETURN)) {
        command = command->next;
        while (command && command->id != CMD_NORMAL)
            command = command->next;
        return command;
    }
    return command->next;
}

static int execute_command_list(struct my_shell *shell, struct cmd_s *command)
{
    pid_t pgid = 0;

    while (command) {
        if (!command->pipe) {
            command = command->next;
            continue;
        // } else if (command->id == ID_PARENTHESIS) {
        //     execute_line()
        } else {
            pgid = execute_command(shell, command->pipe, pgid); // ! return value not checked
            if (pgid == -1)
                return -1;
            shell->n_return = get_command_status(shell, command->pipe, pgid);
        }
        command = get_next_command(command, shell->n_return);
    }
    return 0;
}

int execute_line(struct my_shell *shell, char *line)
{
    struct token_node *token_head = create_token_list_from_line(line);
    struct cmd_s *commands;

    if (!token_head)
        return -1;
    free(line);
    commands = separate_token_list(token_head);
    if (!commands)
        return -1;
    if (pipe_parser(commands) == -1)
        return -1;
    execute_command_list(shell, commands); // ! return value not checked
    delete_token_node_list(token_head);
    // delete_command(); // TODO: code this
    return 0;
}
