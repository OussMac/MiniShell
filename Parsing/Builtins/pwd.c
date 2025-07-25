#include "../minishell.h"

void pwd(char **env)
{
    int x;
    int y;

    x = 0;
    y = 4;
    while (env[x])
    {
        if (ft_strnstr(env[x], "PWD=", 4))
            break;
        x++;
    }
    while(env[x][y])
    {
        write(1, &env[x][y], 1);
        y++;
    }
    write(1, "\n", 1);
}