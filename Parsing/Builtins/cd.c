#include "../minishell.h"

static char *get_pwd(t_data *data)
{
    int i;
    int index;
    char *oldpwd;

    i = 0;
    index = 0;
    while(!ft_strnstr(data->o_env[index], "PWD=", 4))
        index++;

    oldpwd = malloc(get_len(data->o_env[index]) + 1);
    while(data->o_env[index])
    {
        oldpwd[i] = data->o_env[index];
        i++;
        index++;
    }
    oldpwd[i] = '\0';
    return (oldpwd);
}

void ft_cd(char *path, t_data *data)
{
    char *oldpwd;

    get_pwd(data);
    if (chdir(path))
    {
        printf("MasterMind: cd: no such file or directory: %s\n",
            path);
        data->exit_status = 1;
        return ;
    }
}