#include "../../minishell.h"

char *get_variable(char *pointed)
{
    int i;
    char *variable;

    i = 0;
    variable = malloc(get_len(pointed) + 1);
    while(pointed[i])
    {
        variable[i] = pointed[i];
        i++;
    }
    variable[i] = '\0';
    return (variable);
}

// A very useful function to get any variable we need from the env
char    *set_pointer(t_data *data, char *pointed, int len, int mode)
{
	int pindex;
	t_envlist *trav;

	pindex = 0;
	trav = data->env;
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
                trav->pointed = true;
                return("FOUND\n");
            }
            else
                return("NONE\n");
        }
		trav = trav->next;
	}
    return (NULL);
}

void paths_manipulation(char **old_var, char *new_var, int mode)
{
    int i;
    char *new;

    i = 0;
    if (mode == OLDPWD)
    {
        new = ft_strtrim(new_var, "PWD=");
        *old_var = ft_strjoin("OLDPWD=", new);
    }
    else if (mode == PWD)
        *old_var = ft_strjoin("PWD=", new_var);
}

void    change_pwd(t_data *data, char *oldpwd, char *var, int len)
{
    t_envlist *trav;
    char *new;

    set_pointer(data, var, len, POINT_ONLY);
    trav = data->env;
    while (trav != NULL)
    {
        if (trav->pointed == true)
        {
            free(trav->variable);
            if (!ft_strcmp(var, "PWD="))
                paths_manipulation(&trav->variable, oldpwd, PWD);
            else
                paths_manipulation(&trav->variable, oldpwd, OLDPWD);
            trav->pointed = false;
        }
        trav = trav->next;
    }
}