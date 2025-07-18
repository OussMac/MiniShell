#include "../execute.h"


// help function with forbidden functions
// will code our own.
char    *get_absolute_path(char *cmd)
{
    char    *paths[] = {"/bin", "/usr/bin", NULL};
    char    *tmp;
    char    *full_path;
    int     i;

    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path); // Found valid path
        free(full_path);
        i++;
    }
    return (NULL); // Not found
}
//----------------------------------------------------------------------------------

int     exec_node(t_cmd *node, t_osdata *osdata)
{
    int     ex_status;
    pid_t   id = fork();

    if (id == 0)
        exit(exec_colored(node->argv, osdata->env)); // exit child process if execve fails

    waitpid(id, &ex_status, 0);
    return (ex_status);
}

int recursive_execution(t_tree *node, t_data *data)
{
    if (node->tok == COMMAND_ID) // base case exec cmd
    {
        expand_env_variables(node, data->env_vec);
        // print_tree(node);
        // if (validate_builtin(node->argv[0]) == true)
        //     return (exec_builtin(node, data));
        return (exec_node(node, data));
    }
    if (node->tok == PIPE_ID)
        return (pipe_node(node, data)); // handles only to commands rn.
    if (node->tok == PIPE_ID)
    {
        // handle groups
        return (recursive_execution(node->left, data));
    }
    if (node->tok == AND_ID || node->tok == OR_ID)
        return (short_circuit_operand(node, node->tok, data));

    if (node->left)
        return (recursive_execution(node->left, data)); // go deeper left (dfs algo)
    if (node->right)
        return (recursive_execution(node->right, data)); // when done going left go deeper right.
    
    return (EXIT_SUCCESS); // return 0 assume no cmd to execute is success!
}

void    execute_tree(t_tree *root, t_data *data)
{
    if (!root)
    {
        // if (re_built != NULL)
            // Exec list
        return ;
    }
    value_to_argv();
    recursive_execution(root, data);
}