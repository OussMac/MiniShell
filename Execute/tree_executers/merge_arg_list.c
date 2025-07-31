# include "../execute.h"

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

static char *quote_expander(char *str)
{
    int     i;
    char    **lst;
    bool    in_quote;

    i = 0;
    lst = ft_split(str, '\'');
    if (!lst)
        return (NULL);
    print_argv(lst);
    in_quote = false;
    while (str[i])
    {
        if (str[i] = '\'')
        {
            if (!in_quote)
                in_quote = false;
            else
                in_quote = true;
        }

        i++;
    }
    return (str);
}

static char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;

    cur = envlist;
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

static char *expand_var(char *str, t_data *data)
{
    char    *expanded;
    char    **cut_list;
    char    **exp_list;
    bool    first_exp;
    int     i;
    int     count;
    size_t  len;
    char    *val;
    char    *status_temp;
    char    *status_str;

    // special case: string is exactly "$"
    if (o_ft_strncmp(str, "$", 2) == 0)
        return (ft_strdup("$"));

    cut_list = ft_split(str, '$');
    if (!cut_list)
        return (NULL);

    // count how many strings in the list for allocation
    count = 0;
    while (cut_list[count])
        count++;

    // allocate expanded list of pointers to chars char **agv.
    exp_list = malloc(sizeof(char *) * (count + 2)); // +1 for possible trailing $, if not just close it with NULL 
    if (!exp_list)
        return (free_argv(cut_list), NULL); // free previously allocated cutlist

    first_exp = (str[0] == '$'); //flag to check if first is also expandable
    i = 0;
    while (cut_list[i])
    {
        if (i == 0 && !first_exp)
            exp_list[i] = ft_strdup(cut_list[i]); // if this fails.
        else if (cut_list[i][0] == '\0') // just "$"
            exp_list[i] = ft_strdup("$"); // if this fails.
        else if (cut_list[i][0] == '?')
        {
            // $? is handled here
            status_str = o_ft_itoa(data->exit_status); // check if this fails.
            if (cut_list[i][0] != '\0') // [$][?][d][d][\0]  this case.
            {
                status_temp = ft_strjoin(status_str, cut_list[i] + 1); // check if this fails.
                free(status_str);
                exp_list[i] = status_temp;
            }
            else // this case [$][?][\0]
                exp_list[i] = status_str;
        }
        else
        {
            val = find_in_env(data->env, cut_list[i]);
            printf(YLW"%s"RST"\n", val);
            if (val != NULL)
                exp_list[i] = val;
            else
                exp_list[i] = ft_strdup(""); // if this fails.
        }
        i++;
    }

    // edge case if at the end there is a dollar
    len = o_ft_strlen(str);
    if (len > 0 && str[len - 1] == '$')
    {
        exp_list[i] = ft_strdup("$");  // preserve literal trailing $
        i++;
    }

    exp_list[i] = NULL; //close the list

    free_argv(cut_list);
    expanded = list_to_string(exp_list); // convert the list to one single stirng.
    free_argv(exp_list);
    return (expanded);
}

// static char *convert_to_string(t_arg *arg)
// {
//     arg->
// }

static char *rewrap_inquotes(char *str)
{
    int     i;
    int     j;
    size_t  len;
    char    *new;

    len = o_ft_strlen(str);
    new = malloc ((size_t)(len + 2 + 1)); // for ' ' and \0
    if (!new)
        return (NULL);
    new[0] = '\'';
    i = 1;
    j = 0;
    while (str[j])
    {
        new[i] = str[j];
        j++;
        i++;
    }
    new[i++] = '\'';
    new[i] = '\0';
    return (new);
}

static bool still_s_quotes(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\'')
            return (true);
        i++;
    }
    return (false);
}

void    expand_list(t_arg *arg, t_data *data)
{
    t_arg   *curr;
    char    *expanded;
    char    *trimmed;
    char    *edge_clean;

    curr = arg;
    while (curr)
    {
        if (!curr->was_s_quote)
        {
            if (still_s_quotes(curr->value))
            {
                // edge_clean = trim_edge_quotes(curr->value); // check if this fails.
                // free(curr->value);
                // expanded = expand_var(edge_clean, data); // check if fails
                // free(edge_clean);
                // curr->value = rewrap_inquotes(expanded);
                // free(expanded);

                // better algo get curr->val
                // send it to quote_expander
                expanded = quote_expander(curr->value);
                free(curr->value);
                curr->value = expanded;
            }
            else
            {
                expanded = expand_var(curr->value, data); // check if fails
                free(curr->value);
                curr->value = expanded;
            }
        }
        else
        {
            trimmed = trim_edge_quotes(curr->value);
            free(curr->value);
            curr->value = trimmed;
        }
        curr = curr->next;
    }

}

static void print_exp_list(t_arg *arg)
{
    while (arg)
    {
        printf("[ %s ]\n", arg->value);
        printf("was single quoted [ %d ]\n", arg->was_s_quote);
        arg = arg->next;
    }
}


char **convert_list_to_argv(t_arg *arg, t_data *data)
{
    char        **argv;
    size_t      argc;
    int         i;

    argc = arglist_size(arg);
    argv = malloc ((argc + 1)* sizeof(char *));
    if (!argv)
    {
        // cleanup exit;
        return (NULL);
    }
    expand_list(arg, data);
    if (!arg)
        puts("NULL arg");
    print_exp_list(arg);
    i = 0;
    while(arg)
    {
        // argv[i] = convert_to_string(arg);
        // while (arg && !arg->space_next)
        // {
        //     // join_strings();
        //     arg = arg->next;
        // }
        arg = arg->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}
