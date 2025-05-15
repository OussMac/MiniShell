#include "pipex.h"

void    print_from(int from, int until)
{
    while (from < until)
    {
        printf("%d ", from);
        fflush(stdout);
        usleep(2);
        from++;
    }
}

int main()
{
    int start;
    int end;
    int id = fork();
    // we are in the parent if != 0
    if (id != 0)
    {
        start = 5;
        end = 10;
        wait(NULL);
    }
    else
    {
        start = 0;
        end = 5;
    }
    print_from(start, end);
    if (id != 0)
        printf("\n");
        return (EXIT_SUCCESS);
    }