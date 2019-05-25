/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** cd
*/

#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <pwd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "my_string.h"


static int check_chdir_error(const char *path)
{
    DIR *dir;

    if (!path)
        return fprintf(stderr, ": No such file or directory.\n"), -1;
    dir = opendir(path);
    if (access(path, F_OK) || !dir) {
        fprintf(stderr, "%s: %s.\n", path, strerror(errno));
        return -1;
    }
    closedir(dir);
    return 0;
}

static int change_dir(struct my_shell *shell, char *path)
{
    char old_pwd[PATH_MAX] = {0};
    char pwd[PATH_MAX] = {0};

    if (!getcwd(old_pwd, sizeof(old_pwd)))
        return fprintf(stderr, "%s.\n", strerror(errno)), -1;
    if (check_chdir_error(path) == -1)
        return -1;
    if (chdir(path) == -1) {
        fprintf(stderr, "cd: %s.\n", strerror(errno));
        return -1;
    }
    if (!getcwd(pwd, sizeof(pwd)))
        return fprintf(stderr, "%s.\n", strerror(errno)), -1;
    if (set_env(shell, "OLDPWD", old_pwd) == -1
|| set_env(shell, "PWD", pwd) == -1)
        return -1;
    return 0;
}

static int cd_to_home(struct my_shell *shell)
{
    struct passwd *pw = getpwuid(getuid());

    if (!pw)
        return fprintf(stderr, ": No such file or directory.\n"), -1;
    return change_dir(shell, pw->pw_dir);
}

static int cd_old(struct my_shell *shell)
{
    char *old_pwd = my_getenv(shell, "OLDPWD");

    if (!old_pwd)
        return -1;
    return change_dir(shell, old_pwd);
}

int my_cd(struct my_shell *shell, char **av)
{
    size_t len = my_strarraylen(av);

    if (len > 2)
        return fprintf(stderr, TOO_MANY_CD), -1;
    if (len == 1 || (len == 2 && !strcmp("~", av[1])))
        return cd_to_home(shell);
    if (len == 2 && !strcmp("-", av[1]))
        return cd_old(shell);
    if (len == 2)
        return change_dir(shell, av[1]);
    return 0;
}