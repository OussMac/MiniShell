#include "../minishell.h"

void list_env(t_envlist **env, char **envirement)
{
    int i;
    char **var_val;
    t_envlist *node;
    char *value_case;
    char *value_base;

    i = 0;
    while (envirement[i])
    {
        if (!ft_strnstr(envirement[i], "LS_COLORS=", 10))
        {
            var_val = ft_split(envirement[i], '=');
            node = add_variable_value(var_val[0], var_val[1]);
            add_to_env(env, node);
        }
        else if (ft_strnstr(envirement[i], "LS_COLORS=", 10))
        {
            // rememeber this one needs to be modified, if someone created a folder in which = exists
            // it will be splited in the env also in exp
            // CHANGE IT AFTER
            // u can change it in the export workspace to test and verify the new approach
            value_case = ft_strtrim(envirement[i], "LS_COLORS");
            value_base = copy_var(value_case);
            node = add_variable_value("LS_COLORS", value_base);
            add_to_env(env, node);
        }
        i++;
    }
}

void zero_point(t_data *data)
{
    t_envlist *trav;
    t_exportlist *trav_exp;

    trav = data->env;
    trav_exp = data->exp;
    while (trav != NULL)
    {
        trav->pointed = false;
        trav = trav->next;
    }
    while(trav_exp != NULL)
    {
        trav_exp->pointed = false;
        trav_exp = trav_exp->next;
    }
}

void init_data_struct(t_data *data, char **env)
{
    data->append = 0;
    data->to_env = 0;
    data->to_exp = 0;
    data->is_child = 0;
    data->here_minus = 0;
    data->exit_status = 0;
    data->fail = 0;
    data->i = 0;
    data->env = NULL;
    data->exp = NULL;
    data->env_vec = NULL;
    data->saved_in = -1;
    data->saved_out = -1;
    data->env_is_set = false;
    data->pid = 1111;
    // list_exp(&data->exp, env);
    // list_env(&data->env, env);
    // zero_point(data);
    // scan_ops(&data->exp);
    // linkednev_db(&data->env);
    // printf("**************************************************\n");
    // linkednexp_db(&data->exp);
}

