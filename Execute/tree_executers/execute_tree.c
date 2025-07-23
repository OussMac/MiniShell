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
        // expand_env_variables(node, data);
        if (validate_builtin(node->argv[0]) == true)
            return (exec_builtin(node, data));
        if (node->red)
            return (handle_red(node, data));
        return (exec_node(node, data));
    }
    if (node->tok == PIPE_ID)
        return (execute_pipeline(node, data, STDIN_FILENO)); // pipeline recurses back to this func
    if (node->tok == AND_ID || node->tok == OR_ID)
    {
        if (node->red)
            return (handle_red(node, data));
        return (short_circuit_operand(node, node->tok, data));
    }
    if (node->left)
        return (recursive_execution(node->left, data)); // go deeper left (dfs algo)
    if (node->right)
        return (recursive_execution(node->right, data)); // when done going left go deeper right.
    
    return (EXIT_SUCCESS); // return 0 assume no cmd to execute is success!
}

// entry point.
int execute_tree(t_tree *root, t_data *data, char **env, void *re_built)
{
    int rec_exit_status;
    if (!root)
    {
        // if (re_built != NULL)
        {
            // free_tree(root);
            // free_rebuilt(re_built);
            // return (exec_list(NULL)); // passing Null for now.
        }
        free_tree(root);
        printf("Exit Status --> %d\n", data->exit_status);
        return (perror("Null root"), EXIT_FAILURE);
    }
    if (merger(root, data, env) != EXIT_SUCCESS)
    {
        free_tree(root);
        printf("Exit Status --> %d\n", data->exit_status);
        return (perror("Merge Failed"), EXIT_FAILURE);
    }
    rec_exit_status = recursive_execution(root, data);
    return (free_tree(root), rec_exit_status);
}
