#include "../execute.h"

int subshell_group(t_cmd *node, t_osdata *osdata)
{
    pid_t pid = fork();
    if (pid == -1)
        return (perror("fork failed: "), EXIT_FAILURE);
    int status;

    if (pid == 0)
    {
       // child subshell logic, basically runs the executer in a new process
        int exit_status = recursive_execution(node->left, osdata);
        exit(exit_status); // exit with group's exit code
    }
    else
    {
        waitpid(pid, &status, 0); // catch the exit status of the child
        return (WEXITSTATUS(status));
    }

    return (EXIT_FAILURE); // should never happen.
}
