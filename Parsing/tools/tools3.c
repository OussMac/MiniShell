#include "../minishell.h"

void list_env(t_envlist **env, char **envirement)
{
    int i;
    t_envlist *variable;

    i = 0;
    while (envirement[i])
    { 
        variable = add_variable(envirement[i]);
        add_to_env(env, variable);
        i++;
    }
}

void init_data_struct(t_data *data, char **env)
{
    data->exit_status = 0;
    data->env = malloc(sizeof(t_envlist));
}