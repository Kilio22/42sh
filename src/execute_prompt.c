/*
** EPITECH PROJECT, 2019
** PSU_minishell1_2018
** File description:
** Executes the given command
*/

#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "my_string.h"
#include "my_stdio.h"
#include "minishell.h"

static void check_path_isvalid(my_env_t *env)
{
    int index = find_var_index("PATH", env->env);

    if (index == -1)
        restore_var_path(env, "PATH", DEFAULT_PATH);
}

static char *get_command_toexecute(char *command, my_env_t *env)
{
    char **path_vars;
    char *path_cmd;
    int index = find_var_index("PATH", env->env);

    if (access(command, F_OK) == 0)
        return (command);
    if (index == -1) {
        restore_var_path(env, "PATH", DEFAULT_PATH);
        index = find_var_index("PATH", env->env);
    }
    path_vars = my_str_to_path_array(env->env[index]);
    for (int i = 1; path_vars[i] != 0; i++) {
        path_cmd = my_strcat(my_strdup("/"), my_strdup(command));
        path_cmd = my_strcat(my_strdup(path_vars[i]), path_cmd);
        if (access(path_cmd, F_OK) == 0)
            return (path_cmd);
    }
    my_dprintf(2, "%s: Command not found.\n", command);
    return (NULL);
}

static void execute_forked_process(char **argv, my_env_t *env)
{
    argv[0] = get_command_toexecute(argv[0], env);
    if (argv[0] == NULL)
        exit(84);
    execve(argv[0], argv, env->env);
    if (errno == ENOEXEC)
        my_dprintf(2, "%s: %s. Wrong Architecture.\n",
argv[0], strerror(errno));
    else
        my_dprintf(2, "%s: %s.\n", argv[0], strerror(errno));
    exit(84);
}

void display_error_message(int sig)
{
    if (sig == SIGFPE)
        my_dprintf(2, "Floating exception\n");
    else
        my_dprintf(2, "%s\n", strsignal(sig));
}

pid_t execute_prompt(char **argv, my_env_t *env)
{
    pid_t child_pid;

    if (!*argv)
        return 0;
    check_path_isvalid(env);
    child_pid = fork();
    if (child_pid == -1) {
        my_dprintf(2, "mysh: %s.\n", strerror(errno));
        exit(84);
    }
    if (child_pid == 0)
        execute_forked_process(argv, env);
    return child_pid;
}
