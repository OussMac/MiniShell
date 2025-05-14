#include "execute.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	free_argv(char **av, bool argc_2)
{
	int	i;

	i = 0;
	if (!argc_2 || !av)
		return ;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;
	
	ptr = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *) malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return ((char *)sub);
}

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	wc;
	size_t	i;

	wc = 0;
	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] != c && s[i])
			i++;
	}
	return (wc);
}

static void	*lst_free(char **lst, size_t j)
{
	while (j > 0)
	{
		free(lst[--j]);
	}
	free(lst);
	return (NULL);
}

static int	fill_word(const char *s, size_t i, char c, size_t *start)
{
	while (s[i] == c)
		i++;
	if (s[i])
		*start = i;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	size_t		start;
	char		**lst;

	if (!s)
		return (NULL);
	lst = (char **) malloc ((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		i = fill_word(s, i, c, &start);
		if (s[i] || s[i - 1] != c)
		{
			lst[j] = ft_substr(s, start, i - start);
			if (lst[j] == NULL)
				return (lst_free(lst, j));
			j++;
		}
	}
	lst[j] = NULL;
	return (lst);
}
