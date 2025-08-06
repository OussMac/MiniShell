#include "../execute.h"

bool    has_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            return (true);
        i++;
    }
    return (false);
}

static  append_delimiter(char *str)
{
    
}

int internal_field_seperator(char *raw, t_data *data, char ***pockets)
{
    char    **mini_pocket;
    char    **new_pocket;
    size_t  mc_argc;
    size_t  i;

    mini_pocket = ft_split(raw, ' '); // might have to add tabs and \n
    if (!mini_pocket)
        return (EXIT_FAILURE);
    mc_argc = arg_count(mini_pocket);
    if (data->pc.j + mc_argc > data->pc.cap)
    {
        new_pocket = realloc_pockets(*pockets, data->pc.j, data->pc.j + mc_argc);
        if (!new_pocket)
            return (free_argv(mini_pocket), EXIT_FAILURE);
        *pockets = new_pocket;
        data->pc.cap = data->pc.j + mc_argc;
    }
    i = 0;
    while (i < mc_argc)
    {
        (*pockets)[data->pc.j] = ft_strdup(mini_pocket[i]);
        if (!(*pockets)[data->pc.j++])
            return (free_argv(mini_pocket), EXIT_FAILURE);
        i++;
    }
    free_argv(mini_pocket);
    return (EXIT_SUCCESS);
}
