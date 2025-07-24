#include "../execute.h"



// for debugging.
void    print_env(t_envlist *env)
{
    t_envlist *cur;

    cur = env;

    while (cur)
    {
        printf(" ==> key [ %s ] ", cur->variable);
        printf(" - value [ %s ] .\n", cur->value);
        cur = cur->next;
    }

}

static t_envlist    *create_envlist(char **envp)
{
    t_envlist *envlist;
    int i;

    i = 0;
    envlist = NULL;
    while (envp[i])
        add_to_envlist(&envlist, envp[i++]);
    return (envlist);
}

static int tree_traverser(t_tree *root, size_t *recurs_count)
{
    if (*recurs_count == RECURS_LIMIT)
        return (EXIT_FAILURE);
    (*recurs_count)++;
    if (root->tok == COMMAND_ID)
    {
        root->argv = ft_split(root->value, ' ');
        if (!root->argv)
        {
            // clean_up();
            // EXIT_FAILURE;
        }
        return (EXIT_SUCCESS);
    }
    if (root->left)
    {
        if (tree_traverser(root->left, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    if (root->right)
    {
        if (tree_traverser(root->right, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static int  merge_env(t_data *data, char **env)
{
    data->env = create_envlist(env);
    if (!data->env)
        return (EXIT_FAILURE);
    data->env_vec = convert_list_to_envp(data->env);
    if (!data->env_vec)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

// entry point.
int merger(t_tree *root, t_data *data, char **env)
{
    static size_t   r_c;

    if (tree_traverser(root, &r_c) != EXIT_SUCCESS)
    {
        r_c = 0;
        return (perror("Recursion Limit"), EXIT_FAILURE);
    }
    r_c = 0;
    if (merge_env(data, env) != EXIT_SUCCESS)
    {
        // here not cleaned up yet check all the things that happen in merge_env.
        return (perror("Failed To Merge ENV"), EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}