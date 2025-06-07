#include "../minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        // rl_replace_line("", 0);    // bdl lcurrent input b empty string.
	    printf("\n");              // print newline to jump to nl.
	    rl_on_new_line();          // prepare readline for a new line.
	    rl_redisplay();            // redraw prompt.
    }
    else if (signum == SIGQUIT)
        return ;
}
