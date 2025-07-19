#include "../execute.h"

int execute_pipeline(t_tree *node, t_data *data, int input_fd, bool is_last)
{
    int pipefd[2];
    pid_t pid;
    int status;

    if (!node)
        return EXIT_FAILURE;

    // If it's a pipe node, handle recursively
    if (node->tok == PIPE_ID)
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
            exit(execute_pipeline(node->left, data, STDIN_FILENO, false));
        }

        close(pipefd[1]); // parent doesn't write
        if (input_fd != STDIN_FILENO)
            close(input_fd);

        // Recurse on right side with new input (pipe read)
        int right_status = execute_pipeline(node->right, data, pipefd[0], is_last);
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
        exit(recursive_execution(node, data));
    }

    if (input_fd != STDIN_FILENO)
        close(input_fd);

    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}
