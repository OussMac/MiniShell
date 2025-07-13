#include "../execute.h"

void expand_env_variables(t_cmd *node, char **env)
{
    int i = 0;
    char *new_arg;

    while (node->argv[i]) // loop through the entire argvector of the node
    {
        if (node->argv[i][0] == '$') // if $ case
        {
            // skip $ + 1 : $variable ==> variable
            char *value = get_env_value(node->argv[i] + 1, env);
            new_arg = ft_strdup(value);
            free(node->argv[i]);
            node->argv[i] = new_arg;
        }
        else if (node->argv[i][0] == '~')
        {
            char *home = get_env_value("HOME", env);
            new_arg = ft_strjoin(home, node->argv[i] + 1);
            free(node->argv[i]);
            node->argv[i] = new_arg;
        }
        i++;
    }
}
