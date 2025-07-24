#include "../execute.h"

int	o_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (i < n && (s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

bool    has_quotes(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            return (true);
        i++;
    }
    return (false);
}

char	*list_to_string(char **lst)
{
	char	*joined;
	char	*temp;
	size_t	i;

	i = 0;
	joined = NULL;
	while (lst[i])
	{
		temp = joined;
		joined = ft_strjoin(joined, lst[i]);
		if (!joined)
		{
			// free temp
			// return NULL
		}
		free(temp);
		i++;
	}
	return (joined);
}

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}