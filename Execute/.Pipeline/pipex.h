#ifndef PIPEX_H
# define PIPEX_H


// text colors
# define RED "\e[31m"
# define GRN "\e[32m"
# define BLU "\e[34m"
# define YLW "\e[33m"
# define RST "\e[97m"

# include <stdlib.h> // for malloc, constants
# include <unistd.h> // for write, fork
# include <sys/types.h> // for pid_t
#include <wait.h>
# include <stdbool.h> // for bool

# include <stdio.h> // for printf


typedef struct s_data
{
    int pipe_count;
    int cmd_count;
} t_data;



char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t  ft_wordcount(char const *s, char c);


void	free_argv(char **av, bool argc_2);


#endif // PIPEX_H