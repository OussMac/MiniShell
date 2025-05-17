#include "../minishell.h"

void ft_exit(char **argv, t_data *data)
{
    long exit_call;

    if (argv[0] == NULL)
    {
        if (!data->is_child)
            printf("exit\n");
        exit(data->exit_status);
    }
    exit_call = ft_atol(argv[0]);
    if (exit_call == ANOMALY)
    {
        printf("Master@mind: exit: %s: numeric argument required\n", argv[0]);
        exit(2);
    }
    exit(exit_call);
}