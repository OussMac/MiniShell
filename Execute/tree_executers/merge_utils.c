#include "../execute.h"

static int tree_traverser(t_tree *root, char **og_env, size_t *recurs_count)
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
        return (EXIT_SUCCESS);
    }
    if (root->left)
    {
        if (tree_traverser(root->left, og_env, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    if (root->right)
    {
        if (tree_traverser(root->right, og_env, recurs_count) != EXIT_SUCCESS)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// entry point.
int merger(t_tree *root, t_data *data, char **env)
{
    static size_t   r_c;
    if (tree_traverser(root, env, &r_c) != EXIT_SUCCESS)
    {
        r_c = 0;
        return (perror("Recursion Limit"), EXIT_FAILURE);
    }
    r_c = 0;
    return (EXIT_SUCCESS);
}