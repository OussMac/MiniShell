#include "../execute.h"



static int red_in(t_tree *node, t_data *data)
{
    return (EXIT_SUCCESS);
}

static int red_out(t_tree *node, t_data *data)
{
    return (EXIT_SUCCESS);
}

int handle_red(t_tree *node, t_data *data)
{
    if (node->tok == OUTPUT_FILE_ID)
        red_out(node, data);
    else if (node->tok == INPUT_FILE_ID)
        red_in(node, data);
    return (EXIT_SUCCESS);
}