#include "../minishell.h"

void ft_cd(char *path, t_data *data)
{
    char *oldpwd;
    char *no_path;
    char *t_pwd_n;
    char t_pwd[500];
    
    if (!path)
    {
        path = ft_strtrim(set_pointer(data, "HOME=", 5, POINT_N_GET), "HOME=\n");
        no_path = ft_strjoin(path, "/"); // why the chdir does not work without this /, and it works if i type it directly in chdir
        printf("no path arg > %s\n", path);
    }
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
        data->exit_status = 1;
    }
    t_pwd_n = ft_strjoin(t_pwd, N_LINE);
    oldpwd = set_pointer(data, "PWD=", 4, POINT_N_GET);
    change_pwd(data, t_pwd_n, "PWD=", 4); // create another OLDPWD
    change_pwd(data, oldpwd, "OLDPWD=", 7); // overwrite the OLDPWD into PWDPWD since it has already a PWD at start
    // resulting in no OLDPWD to exist (null) when printed
}