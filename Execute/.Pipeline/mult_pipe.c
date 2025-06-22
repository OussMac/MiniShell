#include "pipex.h"


char *join_argv(char **argv, char *delimiter)
{
    int i = 0;
    char *str = NULL;
    char *temp = NULL;

    while (argv[i])
    {
        if (i == 0)
            str = ft_strdup(argv[i]);
        else
        {
            temp = str; // store the current string in temp
            str = ft_strjoin(str, delimiter);
            free(temp); //free the old string


            temp = str;
            str = ft_strjoin(str, argv[i]);
            free(temp);
        }
        i++;
    }
    return (str); // return the joined string.
}

int pipe_number(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count);
}

void count_cmd_pipes(char *str, t_data *data)
{
    data->pipe_count = pipe_number(str);
    data->cmd_count = ft_wordcount(str, '|');
    printf(GRN"Number of pipes: %d\n", data->pipe_count);
    printf("Number of commands: %d\n"RST, data->cmd_count);fflush(stdout);
}

void print_int_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

char *bin_to_absolute(char *cmd)
{
    char *path = getenv("PATH");
    if (!path)
        return (NULL);
    char **paths = ft_split(path, ':');
    if (!paths)
        return (NULL);
    char *bin_path = NULL;
    for (int i = 0; paths[i]; i++)
    {
        bin_path = ft_strjoin(paths[i], "/");
        bin_path = ft_strjoin(bin_path, cmd);
        if (access(bin_path, X_OK) == 0)
            break;
        free(bin_path);
        bin_path = NULL;
    }
    free_argv(paths, true);
    return (bin_path);
}

void execute_one_cmd(char *cmd) // return value to protect from failure
{
    char **args = ft_split(cmd, ' ');
    if (!args)
        return;
    execve(bin_to_absolute(args[0]), args, NULL);
}


int main(int argc, char **argv)
{
    t_data data;
    if (argc < 2)
        return (printf("Usage: %s <cmd1> <cmd2> ...\n", argv[0]), EXIT_FAILURE);
    // parsing argvect
    char *str = join_argv(argv + 1, " | ");
    if (!str)
        return (printf("malloc failed\n"), EXIT_FAILURE);
    printf("%s\n", str);
    count_cmd_pipes(str, &data);

    ///////////////////////////////////////////////////////////////////////////////////////////////// ome commad
    if (data.pipe_count == 0) // only one command, execute the one command.
    {
        if (fork() == 0)
        {
            execute_one_cmd(str);
            return (EXIT_FAILURE);
        }
        // parent process
        wait(NULL);
        return (printf("No pipes found\n"), free(str), EXIT_SUCCESS);
    }///////////////////////////////////////////////////////////////////////////////////////////////// two commands
    else if (data.pipe_count == 1) 
    {
        int fds[2];
        if (pipe(fds) == -1)
            return (printf("pipe failed\n"), free(str), EXIT_FAILURE);
        char **cmds = ft_split(str, '|');
        char *cmd1 = cmds[0];
        char *cmd2 = cmds[1];
        if (fork() == 0)
        {
            dup2(fds[1], STDOUT_FILENO); // redirect stdout to pipe write end
            close(fds[0]); // close read end
            close(fds[1]); // close write end
            execute_one_cmd(cmd1);
            return (EXIT_SUCCESS);
        }
        if (fork() == 0)
        {
            dup2(fds[0], STDIN_FILENO); // redirect stdin to pipe read end
            close(fds[1]); // close write end
            close(fds[0]); // close read end
            execute_one_cmd(cmd2);
            return (EXIT_SUCCESS);
        }
        close(fds[1]); // salina bihom fparent
        close(fds[0]);
        // parent process
        while (wait(NULL) > -1)
            ;
        return (printf("Only one pipe found\n"), free(str), EXIT_SUCCESS);
    }

    // int *fds = malloc(sizeof(int) * (data.pipe_count) * 2);
    // if (!fds)
    //     return (printf("malloc failed\n"), EXIT_FAILURE);
    // pipe(fds);

    // print_int_array(fds, (data.pipe_count + 1) * 2);
    // free(fds);
    free(str);
    // count the number of pipes
   return (EXIT_SUCCESS);
}
