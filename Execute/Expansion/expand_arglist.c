#include "../execute.h"

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

// function entry for expanding a variable can be "$HOME" or "this $USER, is $HOME"
static char	*expand_var(char *str, t_data *data)
{
	char	**pockets;
	char	*expanded;

    if (str[0] == '\0')
        return (ft_strdup("")); // empty case.
	pockets = allocate_pockets(str);
	if (!pockets)
		return (NULL);
	if (pocket_insertion(pockets, str, data) != EXIT_SUCCESS)
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