#include "execute.h"





static bool has_star(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '*')
            return (true);
        i++;
    }
    return (false);
}

static int  link_patterns_to_argv(t_tree *node, char *pattern)
{
    
}


// function entry
int expand_wild_cards(t_tree *node)
{
    int i;

    i = 0;
    while (node->argv[i])
    {
        if (has_star(node->argv[i]))
            link_patterns_to_argv(node, node->argv[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}