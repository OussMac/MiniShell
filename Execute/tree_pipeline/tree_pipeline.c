#include "../execute.h"

int execute_pipeline(t_cmd *node, t_osdata *osdata, int input_fd, bool is_last)
{
    int pipefd[2];
    pid_t pid;
    int status;

    if (!node)
        return EXIT_FAILURE;

    // If it's a pipe node, handle recursively
    if (node->id == O_PIPE)
    {
        if (pipe(pipefd) == -1)
            return perror("pipe"), EXIT_FAILURE;

        // Execute left side (producer)
        pid = fork();
        if (pid == 0)
        {
            dup2(input_fd, STDIN_FILENO); // stdin ← input_fd
            dup2(pipefd[1], STDOUT_FILENO); // stdout → pipe write
            close(pipefd[0]); // not used
            close(pipefd[1]);
            if (input_fd != STDIN_FILENO)
                close(input_fd);
            exit(execute_pipeline(node->left, osdata, STDIN_FILENO, false));
        }

        close(pipefd[1]); // parent doesn't write
        if (input_fd != STDIN_FILENO)
            close(input_fd);

        // Recurse on right side with new input (pipe read)
        int right_status = execute_pipeline(node->right, osdata, pipefd[0], is_last);
        waitpid(pid, &status, 0);
        return right_status;
    }

    // Base case: single command
    pid = fork();
    if (pid == 0)
    {
        if (input_fd != STDIN_FILENO)
        {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // If it's not the last, we would have set up another pipe here
        // But since `is_last == true`, stdout is unchanged
        exit(recursive_execution(node, osdata));
    }

    if (input_fd != STDIN_FILENO)
        close(input_fd);

    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}


// static t_pipe_list *flatten_pipe_chain(t_cmd *node)
// {
//     t_pipe_list *list;
//     t_pipe_list *last;
//     t_pipe_list *tail;

//     if (!node)
//         return (NULL);

//     if (node->id != O_PIPE)
//     {
//         list = malloc(sizeof(t_pipe_list));
//         if (!list)
//             return (perror("malloc"), NULL);
//         list->cmd = node;
//         list->next = NULL;
//         return (list);
//     }

//     list = flatten_pipe_chain(node->left);
//     tail = flatten_pipe_chain(node->right);

//     if (!list || !tail)
//         return (NULL);

//     last = list;
//     while (last->next)
//         last = last->next;
//     last->next = tail;
//     return (list);
// }


// int pipe_node(t_cmd *node, t_osdata *osdata)
// {
//     t_pipe_list *plist = flatten_pipe_chain(node);
//     t_pipe_list *current = plist;
//     int prev_fd = -1;
//     int pipefd[2];
//     pid_t pid;
//     int status;

//     while (current)
//     {
//         if (current->next && pipe(pipefd) == -1)
//             return (perror("pipe failed: "), EXIT_FAILURE);

//         pid = fork();
//         if (pid == 0)
//         {
//             if (prev_fd != -1)
//             {
//                 dup2(prev_fd, STDIN_FILENO);
//                 close(prev_fd);
//             }

//             if (current->next)
//             {
//                 dup2(pipefd[1], STDOUT_FILENO);
//                 close(pipefd[0]);
//                 close(pipefd[1]);
//             }

//             exit(recursive_execution(current->cmd, osdata));
//         }

//         if (prev_fd != -1)
//             close(prev_fd);
//         if (current->next)
//         {
//             close(pipefd[1]);
//             prev_fd = pipefd[0];
//         }

//         current = current->next;
//     }

//     while (plist)
//     {
//         wait(&status); // wait for all
//         current = plist->next;
//         free(plist);
//         plist = current;
//     }

//     return (WEXITSTATUS(status));
// }
