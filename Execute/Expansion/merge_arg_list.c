# include "../execute.h"

static	int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		return (11);
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	if (nbr == 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*max_int(char *str)
{
	char	*tmp;
	int		i;

	tmp = "-2147483648";
	i = 0;
	while (tmp[i])
	{
		str[i] = tmp[i];
		i++;
	}
	return (str);
}

char	*o_ft_itoa(int n)
{
	char	*s;
	int		len;

	len = ft_len(n);
	s = (char *) malloc ((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[len--] = 0;
	if (n == 0)
		s[0] = '0';
	if (n == -2147483648)
		return (max_int(s));
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n != 0)
	{
		s[len--] = (n % 10) + 48;
		n /= 10;
	}
	return (s);
}

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*merge_pockets(char **lst)
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

char	*o_ft_strjoin(char *s1, char *s2)
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
	ptr = (char *) malloc ((o_ft_strlen(s1) + o_ft_strlen(s2)) + 1);
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

// delete later
char	*trim_edge_quotes(char *str)
{
    return (NULL);
}

void print_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
    {
        printf("argv[%d] = %s\n", i, argv[i]);
        i++;
    }
}

char *o_ft_strtrim(char *s, char *set)
{
    size_t start = 0;
    size_t end;

    if (!s || !set)
        return NULL;

    // skip leading characters in 'set'
    while (s[start] && ft_strchr(set, s[start]))
        start++;

    end = o_ft_strlen(s);
    if (end == 0)
        return ft_substr(s, 0, 0);

    end--; // move to last character

    // skip trailing characters in 'set'
    while (end > start && ft_strchr(set, s[end]))
        end--;

    // extract trimmed substring
    return ft_substr(s, start, end - start + 1);
}

char *trim_key_spaces(char *key)
{
    char *trimmed;

    if (!key)
        return (NULL);
    trimmed = o_ft_strtrim(key, " \t\n\v\f\r");
    if (!trimmed)
        return (NULL);
    return (trimmed);
}

// find variable in environment.
static char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;
    char        *trimmed_key;

    cur = envlist;
    trimmed_key = trim_key_spaces(key);
    if (!trimmed_key)
        return (NULL);
    free(key); 
    key = trimmed_key;
    while (cur) 
    {
        if (ft_strcmp(key, cur->variable) == 0)
            return (ft_strdup(cur->value)); // return value
        cur = cur->next;
    }
    return (NULL);
}

static size_t   arglist_size(t_arg *arg)
{
    size_t  size;

    size = 0;
    while (arg)
    {
        size++;
        arg = arg->next;
    }
    return (size);
}
/// expand var

static bool ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

// count number of $ in string.
static int	count_dollars(char *s)
{
	int	i;
	int	count;

    i = 0;
    count = 0;
	while (s[i])
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	return (count);
}

static char	**allocate_pockets(char *s)
{
	int		dollar_count = count_dollars(s);
	char	**pockets;

	// for all possible outcomes, dc * 2 = for text befor $VAR and $VAR, + 2 trailing text after + NULL.
	pockets = malloc(sizeof(char *) * (dollar_count * 2 + 2));
	return (pockets);
}

// expands exit status.
static char *expand_special_cases(char *str, t_data *data, int *i)
{
    if (str[*i + 1] == '?')
    {
	    *i += 2; // move $ ? ==> +2 
        return (o_ft_itoa(data->exit_status));
    }
    else if (str[*i + 1] == '$')
    {
        *i += 2; // move $ $ ==> +2 
        return (o_ft_itoa(data->pid));
    }
    return (NULL); // fallback should never happen.
}

static char *expand_key(char *str, t_data *data, int keylen, int *i)
{
    char    *value;
    char    *key;

    key = ft_substr(str, *i + 1, keylen); // trims $ from start, free after
    *i += keylen + 1; // keylen + 1 [$]
    if (!key)
        return (NULL);
	value = find_in_env(data->env, key);
    free(key);
    if (!value)
        return (NULL);
    return (value);
}
// normal text no expansion.
static char *normal_text(char *str, int *i)
{
    int start;

    start = *i;
	while (str[*i] && str[*i] != '$')
			(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char *standalone(int *i)
{
    (*i)++;
    return (ft_strdup("$"));
}

static void init_pocket_struct(t_pocket *pc)
{
    pc->i = 0;
    pc->j = 0;
    pc->keylen = 0;
    pc->value = NULL;
}

// takes string and splits it into parts.
static int	pocket_insertion(char **pockets, char *str, t_data *data)
{
    t_pocket pc;

    init_pocket_struct(&pc);
	while (str[pc.i])
	{
		if (str[pc.i] == '$')
		{
			if (str[pc.i + 1] == '?' || str[pc.i + 1] == '$')
				pockets[pc.j++] = expand_special_cases(str, data, &pc.i);
			else 
			{
                pc.keylen = 0;
				while (ft_isalnum(str[pc.i + 1 + pc.keylen]) || str[pc.i + 1 + pc.keylen] == '_')
					pc.keylen++;
				if (pc.keylen > 0) // valid key
				{
					pc.value = expand_key(str, data, pc.keylen, &pc.i);
					if (pc.value != NULL)
						pockets[pc.j++] = pc.value;
					else
						pockets[pc.j++] = ft_strdup("");
				}
				else // standalone $
					pockets[pc.j++] = standalone(&pc.i);
			}
		}
		else
			pockets[pc.j++] = normal_text(str, &pc.i);
	}
	return (pockets[pc.j] = NULL, pc.j);
}

static char	*pocket_joiner(char **pockets)
{
	char	*res;

	res = merge_pockets(pockets);
	free_argv(pockets);
	return (res);
}

// function entry for expanding a variable can be "$HOME" or "this $USER, is $HOME"
char	*expand_var(char *str, t_data *data)
{
	char	**pockets;
	char	*expanded;

    if (str[0] == '\0')
        return (ft_strdup("")); // empty case.
	pockets = allocate_pockets(str);
	if (!pockets)
		return (NULL);
	if (pocket_insertion(pockets, str, data) < 0)
		return (free_argv(pockets), NULL);
	expanded = pocket_joiner(pockets);
	return (expanded);
}

// core expanding function. expands the argument linked list.
int expand_list(t_arg *arg, t_data *data)
{
    t_arg   *curr;
    char    *expanded;

    curr = arg;
    while (curr)
    {
        if (!curr->was_s_quote) // if not single quoted, expand
        {
            expanded = expand_var(curr->value, data);
            if (!expanded)
                return (EXIT_FAILURE);
            free(curr->value);
            curr->value = expanded;
        }
        // skips over literal strings s quoted, aymane trims those quotes anyway.
        curr = curr->next;
    }
    return (EXIT_SUCCESS);
}


// helper function.
static void print_exp_list(t_arg *arg)
{
    while (arg)
    {
        printf("[ %s ]\n", arg->value);
        printf("was single quoted [ %d ]\n", arg->was_s_quote);
        arg = arg->next;
    }
}

// Joins successive t_arg->value pieces until space_next==true
static char *join_until_space(t_arg **p_arg)
{
    t_arg *curr = *p_arg;
    char  *res = ft_strdup("");
    char  *tmp;

    if (!res)
        return NULL;

    while (curr)
    {
        tmp = o_ft_strjoin(res, curr->value);
        free(res);
        res = tmp;

        // if the parser marked a space after this piece, consume it and stop
        if (curr->space_next)
        {
            curr = curr->next;
            break;
        }
        // otherwise, keep joining the next piece
        curr = curr->next;
    }

    *p_arg = curr;  // advance the caller’s pointer
    return (res);
}

static void    free_arg_list(t_arg *arg)
{
    t_arg   *tmp;

    if (!arg)
        return ;
    while (arg)
    {

        tmp = arg->next;
        free(arg->value);
        free(arg);
        arg = tmp;
    }
}

// entry function
char **convert_list_to_argv(t_arg *arg, t_data *data)
{
    char        **argv;
    size_t      argc;
    int         i;
    t_arg       *free_head;

    free_head = arg;
    argc = arglist_size(arg);
    argv = malloc ((argc + 1)* sizeof(char *));
    if (!argv)
        return (free_arg_list(free_head), NULL); // cleanup return;
    if (expand_list(arg, data) != EXIT_SUCCESS) // expanding.
        return (free_arg_list(free_head), free(argv), NULL);
    i = 0;
    while(arg)
    {
        argv[i] = join_until_space(&arg);  // join as needed using space_next
        if (!argv[i])
        {
            while (i-- > 0) // cleanup on failure
                free(argv[i]);
            return (free(argv), free_arg_list(free_head), NULL);
        }
        i++;
    }
    argv[i] = NULL;
    return (free_arg_list(free_head), argv);
}
