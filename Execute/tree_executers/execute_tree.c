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

int recursive_execution(t_cmd *node, t_osdata *osdata)
{
    if (!node)
        return (EXIT_FAILURE);
    if (node->id == O_CMD) // base case exec cmd
    {
        expand_env_variables(node, osdata->env);
        // print_tree(node);
        if (validate_builtin(node->argv[0]) == true)
            return (exec_builtin(node, osdata));
        return (exec_node(node, osdata));
    }
    if (node->id == O_PIPE)
        return (pipe_node(node, osdata)); // handles only to commands rn.
    if (node->id == O_GROUP)
    {
        // handle groups
        return (recursive_execution(node->left, osdata));
    }
    if (node->id == O_AND || node->id == O_OR)
        return (short_circuit_operand(node, node->id, osdata));

    if (node->left)
        return (recursive_execution(node->left, osdata)); // go deeper left (dfs algo)
    if (node->right)
        return (recursive_execution(node->right, osdata)); // when done going left go deeper right.
    
    return (EXIT_SUCCESS); // return 0 assume no cmd to execute is success!
}

void    execute_tree(t_cmd *root, t_osdata *osdata)
{
    if (!root)
        return ;
    recursive_execution(root, osdata);
}