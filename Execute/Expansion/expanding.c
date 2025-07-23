#include "../execute.h"




static bool is_expandable(char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (str[i++] == '$')
            return (true);
    return (false);
}
static char *expand_variable(char *str, t_data *data)
{
    char    *expanded;

    find_in_env();

    
    return (expanded);
}


void expand_env_variables(t_tree *node, t_data *data)
{
    int i;

    i = 0;
    while (node->argv[i])
    {
        if (is_expandable(node->argv[i]))
        {
            node->argv[i] = expand_variable(node->argv[i], data);
            // pocket_insert
        }
        i++;
    }


}


    // loop throught the argvector 
    // detect $
    // pass through quotetrimmer
    // launch pocket insertion algorithm 
    // ----> inser the new expaned string using the environment 
    //      if env returns NULL: do nothing to the $string
    //      else expand and pocket insert
    //      return new pointer to an expanded string
    //      and free old one