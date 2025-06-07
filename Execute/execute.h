#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdlib.h> // for constants
# include <stdbool.h> // for booleans

// for readline function.
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

#include <unistd.h> // for write

#include <signal.h> // for signal handling.

typedef enum e_cmd_id
{
    cmd,
    redir,
    pipe
} t_cmd_id;


typedef struct s_cmd
{
    t_cmd_id    id; // command type (cmd, redir, pipe)
    char        **argv; // command arguments


}t_cmd;


// parse helpers.
char	**ft_split(char const *s, char c);
void	free_argv(char **av, bool argc_2);

# endif // EXECUTE_H