#include "../minishell.h"

void ft_cd(char *path, t_data *data)
{
    char *oldpwd;
    char *t_pwd_n;
    char t_pwd[500];

    oldpwd = set_pointer(data, "PWD=", 4, POINT_N_GET);
    if (chdir(path))
    {
        printf("MasterMind: cd: no such file or directory: %s\n",
            path);
        data->exit_status = 1;
        return ;
    }
    if (!getcwd(t_pwd, sizeof(t_pwd)))
    {
        printf("Getcwd Failed\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("getcwd path > %s\n", t_pwd);
    t_pwd_n = ft_strjoin(t_pwd, N_LINE);
    change_pwd(data, t_pwd_n, "PWD=", 4); // create another OLDPWD
    change_pwd(data, oldpwd, "OLDPWD=", 7); // overwrite the OLDPWD into PWDPWD since it has already a PWD at start
    // resulting in no OLDPWD to exist (null) when printed
}