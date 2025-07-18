#include "../execute.h"

// int exec_pipe_node(t_cmd *cmd1, t_cmd *cmd2, int *fds, t_osdata *osdata)
// {
//     pid_t id1;
//     pid_t id2;

//     id1 = fork();
//     if (id1 == -1)
//         return (perror("fork failed."), EXIT_FAILURE);
    
//     // handle child 1 logic
//     if (id1 == 0)
//     {
//         dup2(fds[1], STDOUT_FILENO);
//         close(fds[1]);
//         close(fds[0]);
//         execve(get_absolute_path(cmd1->argv[0]), cmd1->argv, osdata->env);
//         perror("[MP] execve failed"); // Print error if execve fails
//         exit(EXIT_FAILURE); // Exit child process if execve fails
//     }
//     id2 = fork();
//     if (id2 == -1)
//         return (perror("fork failed."), EXIT_FAILURE);
    
//     // handle child 1 logic
//     if (id2 == 0)
//     {
//         dup2(fds[0], STDIN_FILENO);
//         close(fds[1]);
//         close(fds[0]);
//         execve(get_absolute_path(cmd2->argv[0]), cmd2->argv, osdata->env);
//         perror("[MP] execve failed"); // Print error if execve fails
//         exit(EXIT_FAILURE); // Exit child process if execve fails
//     }
//     close(fds[1]);
//     close(fds[0]);
//     while (wait(NULL) > -1);

//     return (EXIT_SUCCESS);
// }

// int pipe_node(t_cmd *node, t_osdata *osdata)
// {
//     int fds[2];

//     // create a pipe
//     if (pipe(fds) == -1)
//         return (perror("pipe failure"), EXIT_FAILURE);
//     exec_pipe_node(node->left, node->right, fds, osdata);

//     // printf("%s output ==> | input <== %s\n", node->left->argv[0], node->right->argv[0]);
//     return (EXIT_SUCCESS);
// }


static t_pipe_list *flatten_pipe_chain(t_cmd *node)
{
    t_pipe_list *list;
    t_pipe_list *last;
    t_pipe_list *tail;

    if (!node)
        return (NULL);

    if (node->id != O_PIPE)
    {
        list = malloc(sizeof(t_pipe_list));
        if (!list)
            return (perror("malloc"), NULL);
        list->cmd = node;
        list->next = NULL;
        return (list);
    }

    list = flatten_pipe_chain(node->left);
    tail = flatten_pipe_chain(node->right);

    if (!list || !tail)
        return (NULL);

    last = list;
    while (last->next)
        last = last->next;
    last->next = tail;
    return (list);
}


int pipe_node(t_cmd *node, t_osdata *osdata)
{
    t_pipe_list *plist = flatten_pipe_chain(node);
    t_pipe_list *current = plist;
    int prev_fd = -1;
    int pipefd[2];
    pid_t pid;
    int status;

    while (current)
    {
        if (current->next && pipe(pipefd) == -1)
            return (perror("pipe failed: "), EXIT_FAILURE);

        pid = fork();
        if (pid == 0)
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (current->next)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            exit(recursive_execution(current->cmd, osdata));
        }

        if (prev_fd != -1)
            close(prev_fd);
        if (current->next)
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }

        current = current->next;
    }

    while (plist)
    {
        wait(&status); // wait for all
        current = plist->next;
        free(plist);
        plist = current;
    }

    return (WEXITSTATUS(status));
}

// 9ad lpipeline algo 