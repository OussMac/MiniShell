#include "../execute.h"

#define COLOR_START "\033[32m"  // Green
#define COLOR_END   "\033[0m"

int exec_colored(char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        return perror("pipe"), -1;

    pid = fork();
    if (pid == -1)
        return perror("fork"), -1;

    if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        dup2(pipefd[1], STDERR_FILENO); // Optional: also redirect stderr
        close(pipefd[1]);

        execve(get_absolute_path(argv[0]), argv, envp);
        dprintf(STDERR_FILENO, RED"Migrane: command not found: %s \n"RST, argv[0]);
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[1]); // Close write end
    char buffer[1024];
    ssize_t n;

    // Start color
    write(STDOUT_FILENO, COLOR_START, strlen(COLOR_START));

    // Read output from child and print with color
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, n);
    }

    // End color
    write(STDOUT_FILENO, COLOR_END, strlen(COLOR_END));

    close(pipefd[0]);

    int status;
    waitpid(pid, &status, 0);
    return status;
}
