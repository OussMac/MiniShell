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

void    exec_node(t_cmd *node, t_osdata *osdata)
{
    pid_t id = fork();

    if (id == 0)
    {
        execve(get_absolute_path(node->argv[0]), node->argv, osdata->env);
        perror("execve failed"); // Print error if execve fails
        exit(EXIT_FAILURE); // Exit child process if execve fails
    }

    wait(NULL);
}

void    recursive_execution(t_cmd *node, t_osdata *osdata)
{
    if (!node)
        return ;
    // printf("[ ====== ] 7na f had node ==> %s\n", cmd_id_to_str(node->id));
    if (node->id == O_PIPE)
    {
        // handle pipeline
        pipe_node(node, osdata);
        return;
    }
    else if (node->id == O_CMD)
    {
        // we are in a command we send it to be executed here.
        // print_argv("[ ====== ] with this content ==> ", node->argv);
        exec_node(node, osdata);
    }
    if (node->left)
        recursive_execution(node->left, osdata);
    if (node->right)
        recursive_execution(node->right, osdata);
}

void    execute_tree(t_cmd *root, t_osdata *osdata)
{
    if (!root)
        return ;
    recursive_execution(root, osdata);
}