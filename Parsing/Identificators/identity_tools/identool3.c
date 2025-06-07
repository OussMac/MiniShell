#include "../../minishell.h"

int realt_quotes(char *input, int doubles_case, char *err)
{
    int i;
    int doubles;

    i = 0;
    doubles = 0;
    if (!ft_strchr(input, doubles_case))
        return(1);
    while(input[i])
    {
        if (input[i] == doubles_case)
            doubles++;
        i++;
    }
    if (doubles % 2 != 0)
    {
        // exit status
        print_error(err, NULL, 0);
        return (0);
    }
    return (1);
}