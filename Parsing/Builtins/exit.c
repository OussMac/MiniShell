#include "../minishell.h"

void ft_exit(char **argv, int exit_status)
{
    long exit_call;

    if (argv[0] == NULL)
        exit(exit_status);
    exit_call = ft_atol(argv[0]);
    if (exit_call == -1111)
    {
        printf("Master@mind: exit: %s: numeric argument required\n", argv[1]);
        exit(2);
    }
    exit(exit_call);
}