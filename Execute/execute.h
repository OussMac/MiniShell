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

// parse helpers.
char	**ft_split(char const *s, char c);
void	free_argv(char **av, bool argc_2);

# endif // EXECUTE_H