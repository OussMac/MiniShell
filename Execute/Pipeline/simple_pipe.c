#include "pipex.h"

int main(int argc, char **argv)
{
    (void)argc;
    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("pipe failure");
        return (EXIT_FAILURE);
    }
    
    pid_t id = fork();
    if (id == -1)
    {
        perror("fork failed.");
        return (EXIT_FAILURE);
    }
    
    if (id == 0)
    {
        // we are in the child
        printf("%s\n", argv[1]);
        printf("%s\n", argv[2]);
        dup2(fds[1], STDOUT_FILENO); //rediriect stdout of first command to write end.
        
        close(fds[1]); // salina bihom fchild
        close(fds[0]);
        char *cmd1[] = {argv[1], argv[2], NULL};
        execve(argv[1], cmd1 ,NULL); // ex: ls -l is gonna execute and its output will be redirected into pipe.
        exit (EXIT_FAILURE);
    }
    pid_t id2 = fork();
    if (id2 == 0)
    {
        
        // we are in second child
        dup2(fds[0], STDIN_FILENO);

        close(fds[1]); // salina bihom fsecond child
        close(fds[0]);
        printf("%s\n", argv[3]);
        printf("%s\n", argv[4]);
        char *cmd2[] = {argv[3], argv[4], NULL};
        execve(argv[3], cmd2, NULL);
        exit(EXIT_FAILURE);
    }
    
    close(fds[1]); // salina bihom fparent
    close(fds[0]);

    while (wait(NULL) > -1)
    ;
   return (EXIT_SUCCESS);
}