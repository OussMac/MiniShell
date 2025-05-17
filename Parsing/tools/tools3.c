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

void zero_point(t_data *data)
{
    t_envlist *trav;

    trav = data->env;
    while(trav != NULL)
    {
        trav->pointed = false;
        trav = trav->next;
    }
}

void init_data_struct(t_data *data, char **env)
{
    data->is_child = 0;
    data->exit_status = 0;
    data->env = malloc(sizeof(t_envlist));
    data->env = NULL;
    list_env(&data->env, env);
    zero_point(data);
    // linkednev_db(&data->env);
}

