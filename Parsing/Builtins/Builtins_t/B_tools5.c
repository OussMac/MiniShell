#include "../../minishell.h"

static int check_alpha_exp(char x)
{
    if ('a' <= x && x <= 'z'
        || 'A' <= x && x <= 'Z')
        return (1);
    return (0);
}

int valide_string(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (i == 0 && arg[i] != '_'
            && !check_alpha_exp(arg[i]))
            return (0);
        if((0 <= arg[i] && arg[i] <= 31)
            || arg[i] == 127)
        return (0);
        i++;
    }
    return(1);
}
