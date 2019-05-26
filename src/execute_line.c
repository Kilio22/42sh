/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** execute_line
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_string.h"
#include "builtins.h"
#include "my.h"
#include "shell.h"

static struct cmd_s *get_next_command(struct cmd_s *command, ret_t ret)
{
    if (!command->next)
        return NULL;
    if ((command->next->id == CMD_AND && ret != SUCCESS_RETURN)) {
        command = command->next;
        while (command && (command->id != CMD_NORMAL && command->id != CMD_OR))
            command = command->next;
        return command;
    }
    if (command->next->id == CMD_OR && ret == SUCCESS_RETURN) {
        command = command->next;
        while (command && (command->id != CMD_NORMAL))
            command = command->next;
        return command;
    }
    return command->next;
}

static int execute_command_list(struct my_shell *shell, struct cmd_s *command)
{
    pid_t pgid = 0;
    ret_t ret = 0;

    while (command) {
        if (!command->pipe) {
            command = command->next;
            continue;
        } else {
            pgid = execute_command(shell, command->pipe, pgid);
            if (pgid == -1)
                return 1;
            ret = get_command_status(shell, command->pipe, pgid);
        }
        command = get_next_command(command, ret);
    }
    return ret;
}

int check_special_char(struct cmd_s *cmd, struct my_shell *shell)
{
    struct pipe_s *head;
    int n_val = 0;

    for (; cmd; cmd = cmd->next) {
        if (!cmd->pipe)
            continue;
        for (head = cmd->pipe; head && n_val == 0; head = head->next) {
            loop_apply_alias(&head->token_list, shell->aliases);
            n_val = env_variables_loop(head->token_list, shell);
        }
        if (n_val != 0)
            return -1;
    }
    return 0;
}

ret_t execute_line(struct my_shell *shell, char *line)
{
    struct token_node *token_head = create_token_list_from_line(line);
    struct cmd_s *commands;
    ret_t ret;

    if (!token_head)
        return 1;
    commands = separate_token_list(token_head);
    if (!commands)
        return 1;
    if (pipe_parser(commands) == -1)
        return 1;
    if (check_special_char(commands, shell) == -1)
        return 1;
    ret = execute_command_list(shell, commands);
    if (delete_command(commands) == -1)
        return 1;
    return ret;
}
