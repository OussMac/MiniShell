#include "../execute.h"
#include <string.h>
char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;
    char        *no_equal;

    cur = envlist;
    while (cur)
    {
        no_equal = ft_substr(cur->variable, 0, o_ft_strlen(cur->variable) - 1);
        if (strcmp(key, no_equal) == 0)
            return (ft_strdup(cur->value)); // return value
        cur = cur->next;
    }
    return (NULL);
}


static char *expand_variable(char *str, t_data *data)
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
            exp_list[i] = ft_strdup(cut_list[i]);
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

size_t tokens_list_size(t_exp_tokens *head)
{
    size_t count;
    t_exp_tokens *current;

    current = head;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

char *trim_outer_spaces(char *str)
{
    size_t start;
    size_t end;

    if (!str)
        return (NULL);

    start = 0;
    while (str[start] && o_ft_strlen(str) > start && str[start] == ' ')
        start++;

    end = o_ft_strlen(str);
    while (end > start && str[end - 1] == ' ')
        end--;

    return (ft_substr(str, start, end - start)); // check if this fails.
}

// size_t  single_quote_count(char **list, t_exp_tokens *tokens)
// {
//     size_t          q_count;
//     size_t          i;
//     t_exp_tokens    *prev;

//     i = 0;
//     q_count = 0;
//     prev = tokens;
//     while(list[i] && tokens)
//     {
//         // skip none single quotes
//         if (tokens->is_env_var)
//         {
//             i++;
//             tokens = tokens->next;
//             continue;
//         }
//         // if to the right env var : flag it to be wrapped
//         if (list[i] && list[i][0] == '\'' && tokens->next && tokens->next->is_env_var)
//         {
//             tokens->next->wrap_me = true;
//             q_count++;
//         }
//         else if (list[i] && list[i][0] == '\'' && tokens->double_q)
//         {
//             // hadi needs to be rredone.
//             if ((list[i + 1] && list[i + 1][0] == '\'' || !list[i + 1]) && (i > 0 && list[i - 1] && list[i - 1][0] == '\''))
//                 tokens->wrap_me = true; // flag lone single quotes to be wrapped
//             q_count++;
//         }
//         // if to the left env var : flag it to be wrapped
//         if (tokens->is_env_var && list[i + 1] && list[i + 1][0] == '\'')
//         {
//             tokens->wrap_me = true;
//             q_count++;
//         }
//         i++;
//         prev = tokens;
//         tokens = tokens->next;
//     }
//     return (q_count);
// }

// char    **wrap_back(char **expanded, t_exp_tokens *tokens)
// {
//     size_t  q_count;

//     q_count = single_quote_count(expanded, tokens);
//     printf("char * pointers to cut from allocation ===> %zu\n", q_count);
//     printf("total %zu - quotes %zu = %zu\n", tokens_list_size(tokens), q_count, tokens_list_size(tokens) - q_count);


//     return (NULL); // null for now.
// }



// entry function 
void expand_env_variables(t_tree *node, t_data *data)
{
    t_exp_tokens    *tokens;
    t_exp_tokens    *curr;
    char            **expanded;
    char            *trimmed;
    int             i;




    if (!node)
        return ; // can't ever happen.
    tokens = o_mini_parser(node, data, data->og_input);
    if (!tokens)
        return ; // check for failure.
    expanded = malloc (sizeof(char *) * (tokens_list_size(tokens) + 1));
    if (!expanded)
        return ; // check
    curr = tokens;
    i = 0;
    while (curr)
    {
        if (curr->is_env_var && !curr->single_q)
            expanded[i] = expand_variable(curr->string, data);
        else
        {
            trimmed = trim_outer_spaces(curr->string);
            expanded[i] = ft_strdup(trimmed); // check for fail
        }
        curr = curr->next;
        i++;
    }
    expanded[i] = NULL;
    print_exp_list(tokens);
    
    for (int j = 0; expanded[j]; ++j) {
    printf("< exp %s>\n", expanded[j]);}

    for (int j = 0; node->argv[j]; ++j) {
    printf("< og %s>\n", node->argv[j]);}

    free(node->argv);
    node->argv = expanded;
}

    /*

        bash-3.2$ echo '$HOME' "$HOME"
        $HOME /mnt/homes/oimzilen
        bash-3.2$ echo "'$HOME' "$HOME""
        '/mnt/homes/oimzilen' /mnt/homes/oimzilen

        need to handle this edge case in expanding.


        Important:
        use data of was single quoted or double quoted or mini parse og string.
    */