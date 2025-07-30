#include "../execute.h"

static void print_export_list(t_envlist *env)
{
    t_envlist *curr;

    curr = env;
    while (curr)
    {

        curr = curr->next;
    }
    // free copy
}

static int add_to_export_list(t_envlist **export_lst, t_envlist *env)
{
    t_envlist *exp_node;

    exp_node = malloc(sizeof(t_envlist));
    if (!exp_node)
        return (EXIT_FAILURE);
    exp_node->variable = env->variable;
    exp_node->value = env->value;


    return (EXIT_SUCCESS);
}

static t_envlist    *sort_list(t_envlist **export_lst, t_envlist *env)
{

    while (env)
    {
        if (add_to_export_list(export_lst, env) != EXIT_SUCCESS)
        {
            // clean exp list and return NULL.
        }
        env = env->next;
    }
    return (NULL);
}

// function entry.
int o_export(t_tree *node, t_data *data)
{
    int         argc;
    t_envlist   *export_lst;

    argc = arg_count(node->argv);
    export_lst = NULL;
    if (argc == 1) // only export case.
    {
        // copy and sort list; sorted version.
        if (sort_list(&export_lst, data->env) == NULL)
            return (EXIT_FAILURE);
        print_export_list(data->env);
    }
    return (EXIT_SUCCESS);
}

// when export is called
// export with no arguments
//    --> lists export list.
// export with arguments, we loop over the args
//      --> if includes '=' whe add to the env list.
//      --> exoported flag true
//      --> else false