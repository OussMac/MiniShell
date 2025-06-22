#include "execute.h"
int execute_command(char **argv)
{
    printf("entering execute_command with argv[0]: %s\n", argv[0]); // for debugging purposes
    if (!argv || !argv[0])
    {
        fprintf(stderr, "Error: No command provided\n");
        return 1; // Error code for no command
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1; // Error code for fork failure
    }
    else if (pid == 0) // Child process
    {
        execve(argv[0], argv, NULL); // Use execve instead of execv
        perror("execve"); // If execve fails
        exit(EXIT_FAILURE); // Exit child process with failure
    }
    else // Parent process
    {
        int status;
        waitpid(pid, &status, 0); // Wait for child to finish
        return WEXITSTATUS(status); // Return child's exit status
    }
}


// t_cmd *execute_tree(t_cmd *root)
// {
//     if (!root)
//         return (NULL);

//     printf("Executing node with id: %d\n", root->id); // for debugging purposes
//     print_argv(root->argv); // for debugging purposes

//     if (root->id == NODE_COMMAND)
//         return (execute_command(root->argv));

//     if (root->id == NODE_AND)
//     {
//         int left_status = execute_node(root->left);
//         if (left_status == 0) // success
//             return execute_node(root->right);
//         return left_status;
//     }

//     if (root->id == NODE_OR)
//     {
//         int left_status = execute_node(root->left);
//         if (left_status != 0) // failure
//             return (execute_node(root->right));
//         return left_status;
//     }

//     if (root->id == NODE_GROUP)
//     {
//         pid_t pid = fork();
//         if (pid == 0)
//         {
//             int status = execute_node(root->left);
//             exit(status);
//         }
//         else
//         {
//             int wstatus;
//             waitpid(pid, &wstatus, 0);
//             return WEXITSTATUS(wstatus);
//         }
//     }

//     if (root->id == NODE_PIPE)
//     {
//         // You’ll implement this too, piping left into right
//     }

//     return 0;
// }


int execute_tree(t_cmd **root)
{
    int left_status;
    int right_status;
    int cmd_status;

    if((*root)->id == O_OR)
    {
        // run left, if fails run right
        left_status = execute_tree(&(*root)->left);
        if (left_status == EXIT_FAILURE)
        {
            right_status = execute_tree(&(*root)->right);
            return (right_status);
        }
    }

   if((*root)->id == O_AND)
    {
        // run left, if succedes run right
        left_status = execute_tree(&(*root)->left);
        if (left_status == EXIT_SUCCESS)
        {
            right_status = execute_tree(&(*root)->right);
            return (right_status);
        }
    }
    // handle command base case
    if ((*root)->id == O_CMD)
    {
        cmd_status = execute_command((*root)->argv); // fix this function
        if (cmd_status == EXIT_SUCCESS)
        {
            return (EXIT_SUCCESS);
        }
        else
        {
            return (EXIT_FAILURE);
        }
    }

    return (EXIT_SUCCESS);
}