#include "../execute.h"

static void free_redir(t_red *red)
{
    if (!red)
        return ;
    t_red *tmp;
    while (red)
    {
        tmp = red->next;
        free(red->value);
        free(red);
        red = tmp;
    }
}

static void free_argv(char **argv)
{
    int i;
    if (!argv)
        return ;
    while (argv[i])
    {
        free(argv[i++]);
    }
    free (argv);
}

void    free_tree(t_tree *node)
{
    if (!node)
        return ;

    if (node->left)
        free_tree(node->left);
    if (node->right)
        free_tree(node->right);
    free(node->value);
    free_argv(node->argv);
    free_redir(node->red);
    free(node);
}
