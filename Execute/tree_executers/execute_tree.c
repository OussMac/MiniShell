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

int     exec_node(t_tree *node, t_data *data)
{
    int     ex_status;
    pid_t   id = fork();

    if (id == 0)
    {
        execve(get_absolute_path(node->argv[0]), node->argv, data->env_vec);
        dprintf(STDERR_FILENO, "Migrane: command not found: %s \n", node->argv[0]);
        exit(EXIT_FAILURE); // exit child process if execve fails
    }

    waitpid(id, &ex_status, 0);
    return (ex_status);
}

int recursive_execution(t_tree *node, t_data *data) // not static cuz used in pipeline
{
    if (node->tok == COMMAND_ID) // base case exec cmd
    {
        // expand_env_variables(node, data->env_vec);
        // print_tree(node);
        // if (validate_builtin(node->argv[0]) == true)
        //     return (exec_builtin(node, data));
        return (exec_node(node, data));
    }
    if (node->tok == PIPE_ID)
        return (puts("dkhl"), execute_pipeline(node, data, STDIN_FILENO, false)); // pipeline recurses back to this func
    // if (node->tok == AND_ID || node->tok == OR_ID)
    //     return (short_circuit_operand(node, node->tok, data));
    if (node->left)
        return (recursive_execution(node->left, data)); // go deeper left (dfs algo)
    if (node->right)
        return (recursive_execution(node->right, data)); // when done going left go deeper right.
    
    return (EXIT_SUCCESS); // return 0 assume no cmd to execute is success!
}
// entry point.
int execute_tree(t_tree *root, t_data *data, char **env, void *re_built)
{
    if (!root)
    {
        // if (re_built != NULL)
        //     return (exec_list(NULL)); // passing Null for now.
        return (perror("Null root"), EXIT_FAILURE); // free tree
    }
    if (merger(root, data, env) != EXIT_SUCCESS)
        return (perror("Merge Failed"), EXIT_FAILURE); // free tree
    return (recursive_execution(root, data));
}
