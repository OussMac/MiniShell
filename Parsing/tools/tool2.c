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

long    ft_atol(const char *str)
{
    size_t          i;
    long long       result;
    int                     sign;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
            i++;
    if (str[i] == '-' || str[i] == '+')
    {
            if (str[i] == '-')
                    sign = -1;
            i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
            if (result > (LLONG_MAX - (str[i] - '0')) / 10)
                    return (ANOMALY);
            result = result * 10 + (str[i] - '0');
            i++;
    }
    return (sign * result);
}

char **double_dup(char **env)
{
    int x;
    int y;
    int len;
    char **o_env;

    x = 0;
    len = double_len(env);
    o_env = malloc(len * sizeof(char *) + 1);
    while(x < double_len(env))
    {
        y = 0;
        o_env[x] = malloc(get_len(env[x]) + 1);
        while (env[x][y])
        {
            o_env[x][y] = env[x][y];
            y++;
        }
        o_env[x][y] = '\0';
        x++; 
    }
    o_env[x] = NULL;
    return(o_env);
}

char    *ft_strjoin(char *s1, char *s2)
{
        int             i;
        int             j;
        char    *join;

        if (!s1)
                return (ft_strdup(s2));
        if (!s2)
                return (NULL);
        i = 0;
        j = 0;
        join = malloc(get_len(s1) + get_len(s2) + 1);
        if (join == NULL)
                return (NULL);
        while (s1[i])
        {
                join[i] = s1[i];
                i++;
        }
        while (s2[j])
        {
                join[i] = s2[j];
                j++;
                i++;
        }
        join[i] = '\0';
        return (join);
}
