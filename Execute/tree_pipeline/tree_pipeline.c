#include "../execute.h"

static void cmd_add_last(t_tree *node, t_plist **head)
{
    t_plist *new_pipe_cmd;
    t_plist *curr;

    new_pipe_cmd = malloc(sizeof(t_plist));
    if (!new_pipe_cmd)
        return ;
    new_pipe_cmd->cmd_node = node;
    new_pipe_cmd->next = NULL;
    if (!*head)
        *head = new_pipe_cmd;
    else
    {
        curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new_pipe_cmd;
    }
}

static void flatten_pipeline(t_tree *node, t_plist **head)
{
    t_plist *plist;

    if (!node)
        return ;
    // base case
    if (node->tok == PIPE_ID)
    {
        flatten_pipeline(node->left, head);
        flatten_pipeline(node->right, head);
    }
    else
        cmd_add_last(node, head);
}

static void free_pipe_list(t_plist *head)
{
    t_plist *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int execute_pipeline(t_tree *root, t_data *data, int input_fd)
{
    t_plist *plist = NULL;
    t_plist *curr;
    int prev = input_fd, fd[2], status;
    
    flatten_pipeline(root, &plist);
    curr = plist;
    while (curr)
    {
        int is_pipe = curr->next != NULL;
        if (is_pipe && pipe(fd) < 0)
            return (perror("pipe"), EXIT_FAILURE);
        pid_t pid = fork();
        if (pid < 0)
            return (perror("fork"), EXIT_FAILURE);
        if (pid == 0)
        {
            if (prev != STDIN_FILENO)
                dup2(prev, STDIN_FILENO), close(prev);

            if (is_pipe)
                dup2(fd[1], STDOUT_FILENO), close(fd[0]), close(fd[1]);

            execve(get_absolute_path(curr->cmd_node->argv[0]), curr->cmd_node->argv, data->env_vec);

            dprintf(STDERR_FILENO, "Migrane: command not found: %s\n", curr->cmd_node->argv[0]);
            exit(EXIT_FAILURE);
        }
        if (prev != STDIN_FILENO)
            close(prev);
        if (is_pipe)
            close(fd[1]), prev = fd[0];
        curr = curr->next;
    }
    if (prev != STDIN_FILENO)
        close(prev);
    free_pipe_list(plist);
    while (wait(&status) > 0)
        ;
    return (WEXITSTATUS(status));
}
