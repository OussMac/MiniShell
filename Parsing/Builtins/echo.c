#include "../minishell.h"

static int double_len(char **argv)
{
    int x;
    int len;

    x = 0;
    len = 0;
    while(argv[x])
    {
        len++;
        x++;
    }
    return(len);
}

void echo(char **argv)
{
    int x;
    int y;
    int newline;

    x = 0;
    newline = 0;
    if (!ft_strcmp(argv[x], "-n"))
    {
        x++;
        newline = 1;
    }
    while(x < double_len(argv))
    {
        y = 0;
        while(argv[x][y])
        {
            write(1, &argv[x][y], 1);
            y++;
        }
        x++;
        if (x != double_len(argv))
            write(1, " ", 1);
    }
    if (newline)
        write(1, "\n", 1);
}
