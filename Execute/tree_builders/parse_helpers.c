#include "../execute.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	ptr = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (ptr == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = -1;
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	return ((ptr));
}

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

void	*lst_free(char **lst, size_t j)
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

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2 [i]);
		}
		i++;
	}
	return (0);
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
    else if (signum == SIGQUIT) // remove this later.
        return ;
}

// function to print double char array
void	print_argv(char *name, char **argv)
{
	int	i;

	i = 0;
	printf(GRN"%s: ", name);
	while (argv[i])
	{
		printf("[%s] ", argv[i]);
		i++;
	}
	printf("\n"RST);
}

// simple tokenizer wrapper built on ft_split
t_cmd	*o_tokenizer(char *line,t_osdata *osdata)
{
	char **tokenv = better_split(line);

	print_argv("tokens", tokenv); // debugger to see the tokenz before the tree.
	t_cmd *root = build_tree(osdata, tokenv);
	return (root);
}