#include "../minishell.h"

void ft_env(int unset, char **env)
{
    if (unset)
        return ;
    int x;
    int y;

    x = 0;
    while(env[x])
    {
        y = 0;
        while(env[x][y])
        {
            write(1, &env[x][y], 1);
            y++;
        }
        x++;
        write(1, "\n", 1);
    }
}