#include "execute.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        // rl_replace_line("", 0);    // bdl lcurrent input b empty string.
	    printf("\n");              // print newline to jump to nl.
	    rl_on_new_line();          // prepare readline for a new line.
	    rl_redisplay();            // redraw prompt.
    }
    else if (signum == SIGQUIT) // remove this later.
        return ;
}

int main(void)
{
    char *input;


    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1334)
    {
        input = readline("Master@Mind> ");

        if (!input)
            return (printf("exit\n"), free(input), EXIT_SUCCESS); // handling ctrl-D
        if (input[0])
            add_history(input); // add non-empty strings to history.
        free(input);
    }
    return (EXIT_SUCCESS);
}




