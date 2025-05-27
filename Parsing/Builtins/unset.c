#include "../minishell.h"

static void    nodes_manipulation(t_envlist *trav, t_envlist *f_node,
    t_envlist *l_node, int first)
{
    if (trav->pointed == true)
    {
        if (trav->next != NULL
            && !first)
            l_node = trav->next;
        trav->pointed = false;
        free(trav->variable);
        trav->variable = NULL;
        trav->next = NULL;
        free(trav);
        trav = NULL;
        if (!first)
            f_node->next = l_node;
    }
}

static void eleminate_target(t_data *data)
{
    int i;
    int first;
    t_envlist *trav;
    t_envlist *f_node;
    t_envlist *l_node;

    i = 0;
    first = 0;
    f_node = NULL;
    l_node = NULL;
    trav = data->env;
    while (trav != NULL)
    {
        if (trav->next != NULL
                && trav->next->pointed == true)
               f_node = trav;
        if (i == 0)
            firstnode_handle(trav, data, trav->next, &first);
        nodes_manipulation(trav, f_node, l_node, first);
        if (trav == NULL)
            break;
        trav = trav->next;
        i++;
    }
}

static void eleminate(t_data *data, char **argv, char **env)
{
    int i;

    i = 0;
    while (i < double_len(argv))
    {
        set_pointer(data, argv[i], get_len(argv[i]), POINT_ONLY);
        eleminate_target(data);
        i++;
    }
}

static char    **add_op(char **argv)
{
    int i;
    int y;
    char **argv_op;

    i = 1;
    y = 0;
    argv_op = malloc(double_len(argv) * sizeof(char *) + 1);
    while (argv[i])
    {
        argv_op[y] = ft_strjoin(argv[i], "=");
        i++;
        y++;
    }
    argv_op[y] = NULL;
    return (argv_op);
}

void    unset(char **args, t_data *data)
{
    char **arg_op;

    arg_op = add_op(args);
    eleminate(data, arg_op, data->env);
}