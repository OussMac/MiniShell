#include "../execute.h"


bool    validate_builtin(char *str)
{
    if (ft_strcmp(str, "echo") == 0)
        return (true);
    return (false);
}

int exec_builtin(t_cmd *node, t_osdata *osdata)
{
    if (ft_strcmp(node->argv[0], "echo") == 0)
        return (o_echo(node, osdata));
    return (EXIT_FAILURE);
}