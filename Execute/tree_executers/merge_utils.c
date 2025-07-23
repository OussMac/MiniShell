#include "../execute.h"

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
    {
        add_to_envlist(&envlist, envp[i]);
        printf ("[[ %s ]]\n", envp[i]);
        i++;
    }
    return (envlist);
}

static int tree_traverser(t_tree *root, t_data *data, char **og_env, size_t *recurs_count)
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
        root->env = og_env;
        data->env = create_envlist(og_env);
        if (!data->env)
        {
            // clean_up();
            exit(EXIT_FAILURE);
        }
        print_env(data->env);
        return (EXIT_SUCCESS);
    }
    if (root->left)
    {
        if (tree_traverser(root->left, data, og_env, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    if (root->right)
    {
        if (tree_traverser(root->right, data, og_env, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// entry point.
int merger(t_tree *root, t_data *data, char **env)
{
    static size_t   r_c;
    if (tree_traverser(root, data, env, &r_c) != EXIT_SUCCESS)
    {
        r_c = 0;
        return (perror("Recursion Limit"), EXIT_FAILURE);
    }
    r_c = 0;
    return (EXIT_SUCCESS);
}