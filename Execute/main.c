#include "execute.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}


void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        rl_replace_line("", 0);    // bdl lcurrent input b empty string.
	    printf("\n");              // print newline to jump to nl.
	    rl_on_new_line();          // prepare readline for a new line.
	    rl_redisplay();            // redraw prompt.
    }
    else if (signum == SIGQUIT)
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




