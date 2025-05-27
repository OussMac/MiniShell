#include "../minishell.h"

void scan_ops(t_exportlist **exp)
{
        char *tmp_var;
        char *tmp_value;
        t_exportlist *trav1;
        t_exportlist *trav2;

        trav1 = *exp;
        while(trav1 != NULL)
        {
                trav2 = trav1->next;
                while(trav2 != NULL)
                {
                        if (ft_strcmp(trav1->variable, trav2->variable) > 0)
                        {
                                tmp_var = trav1->variable;
                                tmp_value = trav1->value;
                                trav1->variable = trav2->variable;
                                trav1->value = trav2->value;
                                trav2->variable = tmp_var;
                                trav2->value = tmp_value;
                        }
                        trav2 = trav2->next;
                }
                trav1 = trav1->next;
        }
}

void save_var(char *arg, t_data *data)
{
    t_envlist *set_env;
    t_exportlist *set_exp;

    if (data->to_env)
    {
        if (!data->append && !replace(arg, data, ENV))
            data->to_env = 0;
        else if (data->append)
        {
            if (!change_append(arg, data, ENV))
                data->to_env = 0;
        }
        else
        {
            set_env = add_variable_value(scrap_var(arg), scrap_value(arg));
            add_to_env(&data->env, set_env);
            data->to_env = 0;
        }
    }
    if (data->to_exp)
    {
        if (!data->append && !replace(arg, data, EXP))
            data->to_exp = 0;
        else if (data->append)
        {
            change_append(arg, data, EXP);
            data->to_env = 0;
        }
        else
        {
            set_exp = add_exp_value(scrap_var(arg), scrap_value(arg));
            add_to_exp(&data->exp, set_exp);
            data->to_exp = 0;
            scan_ops(&data->exp);
        }
    }
}

int valide_exp(char *arg, t_data *data)
{
    if (!set_flags(arg, data))
        return(-1);
    save_var(arg, data);
    return(0);
}

void    export(t_data *data, char **args, int len)
{
    int i;
    char *arg;

    i = 1;
    if (len == 1) // to simulate no argument were found
        linkednexp_db(&data->exp);
    while(i <= len - 1)
    {
        if (valide_exp(args[i], data))
        {
            printf("\033[91mMasteMind: Export: Use Of Invlaid Identifer\n\033[0m");
            data->exit_status = 1;
            break;
        }
        else
            printf("\033[32mMasterMind: Export: Valide Syntax\n\033[0m");
        i++;
    }
}