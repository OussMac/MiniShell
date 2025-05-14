#include "../minishell.h"

int check_doubles(char x, char x2)
{
    if ((x == '|' && x2 == '|')
        || (x == '&' && x2 == '&')
        || (x == '>' && x2 == '>')
        || (x == '<' && x2 == '<'))
        return (T);
    return(N);
}

int     ft_strcmp(char *s1, char *s2)
{
        size_t  i;

        if (!s1 || !s2)
            return(-1);
        i = 0;
        while ((s1[i] || s2[i]))
        {
                if (s1[i] != s2[i])
                        return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
                i++;
        }
        return (0);
}