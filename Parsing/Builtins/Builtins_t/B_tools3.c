#include "../../minishell.h"

//Export Tools
char    *set_pointer_exp(t_data *data, char *pointed, int len, int mode)
{
	int pindex;
	t_exportlist *trav;

	pindex = 0;
	trav = data->exp;
	while (trav != NULL)
	{
        if (mode == POINT_N_GET)
        {
            if (!ft_strncmp(trav->variable, pointed, len))
                return (get_variable(trav->variable));
        }
        else if (mode == POINT_ONLY)
        {
            if (!ft_strncmp(trav->variable, pointed, len))
            {
                printf("set_pointer exp pointed > %s%s\n", trav->variable, trav->value);
                trav->pointed = true;
                return("FOUND\n");
            }
        }
		trav = trav->next;
	}
    return (NULL);
}

int set_flags(char *arg, t_data *data)
{
    if (ft_strchr(arg, '='))
    {
        data->to_env = 1;
        data->to_exp = 1;
        if (to_append(arg))
            data->append = 1;
    }
    else
    {
        if (!valide_string(arg))
            return(0);
        data->to_exp = 1;
    }
    return (1);
}

int to_append(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        // printf("char arg > %c\n", arg[i]);
        if (i == 0 && arg[i] == '=')
            break;
        if(arg[i + 1] == '='
            && arg[i] == '+')
            return(1);
        i++;
    }
    return (0);
}

char *scrap_var(char *arg)
{
    int i;
    int len;
    char *var;

    i = 0;
    len = 0;
    while(arg[i] != '=')
    {
        len++;
        i++;
    }
    var = malloc(len + 1);
    i = 0;
    while(arg[i] != '=')
    {
        var[i] = arg[i];
        if (arg[i] == '+')
            break;
        i++;
    }
    var[i] = '\0';
    return(var);
}

char *scrap_value(char *arg)
{
    int i;
    int j;
    int len;
    char *value;

    i = 0;
    j = 0;
    len = 0;
    while (arg[i] != '=')
        i++;
    i++;
    len = get_len(&arg[i]);
    value = malloc(len + 1);
    while (arg[i])
    {
        value[j] = arg[i];
        j++;
        i++;
    }
    value[j] = '\0';
    return (value);
}