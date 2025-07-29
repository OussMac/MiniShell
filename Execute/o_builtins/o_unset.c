#include "../execute.h"

static size_t  arg_count(char **argv)
{
    size_t  argc;

    argc = 0;
    while (argv[argc])
        argc++;
    return (argc);
}

static t_envlist *get_before_last(t_envlist *env)
{
    while (env->next->next) // protect from segfault.
        env = env->next;
    return (env);
}

static t_envlist *get_last(t_envlist *env)
{
    while (env->next)
        env = env->next;
    return (env);
}


static  void delete(t_envlist *node)
{
    free(node->value);
    free(node->variable);
    free(node);
}

static void delete_node(t_envlist **env, t_envlist *to_delete)
{
    t_envlist *last_node;
    t_envlist *before_last;
    t_envlist *curr;

    curr = *env;
    last_node = get_last(*env);
    if (curr == to_delete) // First node
    {
        if (curr->next)
        {
            curr = curr->next;
            delete(*env);
            *env = curr;
        }
        else
        {
            delete(*env);
            *env = NULL;
        }
    }
    else if (last_node == to_delete)
    {
        before_last = get_before_last(*env);
        before_last->next = NULL;
        delete(last_node);
    }
    else
    {
        // code algo if was in the middle tmr.
    }

}

// scans the envlist and finds argument node to unset it.
static void unset_node(char *argument, t_envlist **env)
{
    t_envlist *curr;

    if (!*env)
        return ; // gotta check if env is 
    curr = *env;
    while (curr)
    {
        if (o_ft_strncmp(argument,curr->variable , o_ft_strlen(argument)) == 0) // found env variable.
            delete_node(env, curr);
        curr = curr->next;
    }

}

// function entry.
int o_unset(t_tree *node, t_data *data)
{
    size_t      argc;
    int         i;

    argc = arg_count(node->argv);
    if (argc == 1)
        return (EXIT_SUCCESS);
    i = 1;
    while (node->argv[i])
    {
        unset_node(node->argv[i], &data->env);
        i++;
    }
    return (EXIT_SUCCESS);
}


// itereate through the lest 
    // use strncmp on the argv arguments to find the variable to unset and delete it from the list
    // if the varibale doenst exit do nothing
    // if the unset is called with 0 args do nothing



   // some functions set env to null protect dont forget all functions that access env