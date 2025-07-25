#include "../../minishell.h"

char *add_slash(char *value)
{
    int i;
    int j;
    int slash_count;
    char *new_value;

    if (!ft_strchr(value, '\"'))
        return (value);
    i = 0;
    j = 0;
    slash_count = 0;
    while (value[i])
    {
        if (value[i] == '\"'
            || value[i] == '$')
            slash_count++;
        i++;
    }
    new_value = malloc(get_len(value) + slash_count + 1);
    i = 0;
    while(value[i])
    {
        if (value[i] == '\"'
            || value[i] == '$')
        {
            new_value[j] = '\\';
            j++;
        }
        new_value[j] = value[i];
        i++;
        j++;
    }
    new_value[j] = '\0';
    return (new_value);
}

void   change_value(t_data *data, char *arg, int mode)
{
    char *declare_var;
    char *var_value;
    t_envlist *trav;
    t_exportlist *trav_exp;

    trav = data->env;
    trav_exp = data->exp;
    if (mode == ENV)
    {
        while(trav != NULL)
        {
            if (trav->pointed == true)
            {
                free(trav->variable);
                free(trav->value);
                trav->pointed = false;
                trav->variable = ft_strjoin(scrap_var(arg), "=");
                trav->value = scrap_value(arg);
            }
            trav = trav->next;
        }
    }
    else if (mode == EXP)
    {
        while (trav_exp != NULL)
        {
            if (trav_exp->pointed == true)
            {
                free(trav_exp->variable);
                free(trav_exp->value);
                trav_exp->pointed = false;
                declare_var = ft_strjoin("declare -x ", scrap_var(arg));     
                var_value = ft_strjoin("=\"", add_slash(scrap_value(arg)));
                trav_exp->variable = declare_var;
                trav_exp->value = ft_strjoin(var_value, "\"");
            }
            trav_exp = trav_exp->next;
        }
    }
}

int replace(char *arg, t_data *data, int mode)
{
    char *cmp;
    char *var_name;

    if (mode == ENV)
    {
        var_name = scrap_var(arg);
        cmp = set_pointer(data, var_name, get_len(var_name), POINT_ONLY);
        if (!ft_strncmp(cmp, "FOUND\n", 6))
        {
            change_value(data, arg, ENV);
            return (0);
        }
    }
    if (mode == EXP)
    {
        var_name = ft_strjoin("declare -x ", scrap_var(arg));
        cmp = set_pointer_exp(data, var_name, get_len(var_name), POINT_ONLY);
        if (!ft_strncmp(cmp, "FOUND\n", 6))
        {
            change_value(data, arg, EXP);
            return(0);
        }
    }
    return (1);
}

void append(t_data *data, char *arg, int mode)
{
    t_envlist *trav;
    t_exportlist *trav2;
    char *new_exp_value;
    char *quoted1;
    char *quoted2;

    trav = data->env;
    trav2 = data->exp;
    if (mode == ENV)
    {
        while(trav != NULL)
        {
            if(trav->pointed == true)
            {
                printf("trav pointed > %s%s\n", trav->variable, trav->value);
                // we may free here
                // free(trav->value);
                printf("joining this %s with %s\n", trav->value, scrap_value(arg));
                trav->value = ft_strjoin(trav->value, scrap_value(arg));
                trav->pointed = false;
            }
            trav = trav->next;
        }
    }
    else if (mode == EXP)
    {
        while (trav2 != NULL)
        {
            if (trav2->pointed == true)
            {
                printf("trav value > %s\n", trav2->value);
                new_exp_value = ft_strtrim(trav2->value, "=\"");
                printf("new_exp_value > %s\n", new_exp_value);
                // we may free here
                quoted1 = ft_strjoin("=\"", new_exp_value);
                quoted2 = ft_strjoin(quoted1, add_slash(scrap_value(arg)));
                trav2->value = ft_strjoin(quoted2, "\"");
            }
            trav2 = trav2->next;
        }
    }
}

int change_append(char *arg, t_data *data, int mode)
{
    char *cmp;
    char *var_name;

    if(mode == ENV)
    {
        var_name = scrap_var(arg);
        cmp = set_pointer(data, var_name, get_len(var_name), POINT_ONLY);
        if (!ft_strncmp(cmp, "FOUND\n", 6))
        {
            append(data, arg, ENV);
            return (0);
        }
    }
    if (mode == EXP)
    {
        var_name = ft_strjoin("declare -x ", scrap_var(arg));
        cmp = set_pointer_exp(data, var_name, get_len(var_name), POINT_ONLY);
        if (!ft_strncmp(cmp, "FOUND\n", 6))
        {
            append(data, arg, EXP);
            return(0);
        }
    }
    return (1);
}