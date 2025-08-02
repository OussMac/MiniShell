# include "../execute.h"

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

    key = ft_substr(str, *i + 1, keylen); // trims $ from start
    if (!key)
        return (NULL);
	value = find_in_env(data->env, key);
    if (!value)
        return (NULL);
    *i += keylen + 1; // keylen + 1 [$]
    return (value);
}
// normal text no expansion.
static char *normal_text()
{

}

// takes string and splits it into parts.
static int	pocket_insertion(char **pockets, char *s, t_data *data)
{
	int		i;
	int		j;
	int		keylen;
	char	*key;
	char	*value;
	int		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] == '?' || s[i + 1] == '$')
				pockets[j++] = expand_special_cases(s, data, &i);
			else
			{
				keylen = 0;
				while (ft_isalnum(s[i + 1 + keylen]) || s[i + 1 + keylen] == '_')
					keylen++;
				if (keylen > 0) // valid key
				{
					value = expand_key(s, data, keylen, &i);
					if (value != NULL)
						pockets[j++] = value;
					else
						pockets[j++] = ft_strdup("");
				}
				else // standalone $
				{
					pockets[j++] = ft_strdup("$");
					i++;
				}
			}
		}
		else
		{
			start = i;
			while (s[i] && s[i] != '$')
				i++;
			pockets[j] = ft_substr(s, start, i - start);
			j++;
		}
	}
	pockets[j] = NULL;
	return (j);
}

static char	*pocket_joiner(char **parts)
{
	char	*res;

	res = list_to_string(parts);
	free_argv(parts);
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
    return res;
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

    argc = arglist_size(arg);
    argv = malloc ((argc + 1)* sizeof(char *));
    if (!argv)
        return (free_arg_list(arg), NULL); // cleanup return;
    if (expand_list(arg, data) != EXIT_SUCCESS) // expanding.
        return (free_arg_list(arg), free(argv), NULL);
    i = 0;
    while(arg)
    {
        argv[i] = join_until_space(&arg);  // join as needed using space_next
        if (!argv[i])
        {
            // cleanup on failure
            while (i-- > 0) 
                free(argv[i]);
            free(argv);
            return (NULL);
        }
        i++;
    }
    argv[i] = NULL;
    return (argv);
}
