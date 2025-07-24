#include "../execute.h"

char    *find_in_env(t_envlist *envlist, char *key)
{
    t_envlist   *cur;

    cur = envlist;
    while (cur)
    {
        if (o_ft_strncmp(key, cur->variable, o_ft_strlen(key)) == 0)
            return (ft_strdup(cur->value)); // return value
        cur = cur->next;
    }
    return (NULL);
}



static bool is_expandable(char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (str[i++] == '$')
            return (true);
    return (false);
}


// static char *expand_variable(char *str, t_data *data)
// {
//     char    *expanded;
//     char    **cut_list;
//     char    **exp_list;
//     bool    first_exp;
//     int     i;
//     int     count;

//     cut_list = ft_split(str, '$');
//     if (!cut_list)
//         return (NULL);
//     count = 0;
//     while (cut_list[count])
//         count++;
//     exp_list = malloc(sizeof(char *) * (count + 1));
//     if(!exp_list)
//         return (free_argv(cut_list), NULL);
    
//     first_exp = false;
//     if (str[0] == '$') // edge case if first is also expandable
//         first_exp = true;
//     i = 0;
//     while(cut_list[i])
//     {
//         if (i == 0 && !first_exp)
//             exp_list[i] = ft_strdup(cut_list[i]);
//         else
//             exp_list[i] = find_in_env(data->env, cut_list[i]);
//         // if (!exp_list[i])
//             // free what was allocated before return (NULL)
//         i++;
//     }
//     exp_list[i] = NULL;
//     free_argv(cut_list);
//     expanded = list_to_string(exp_list);
//     free_argv(exp_list);
//     return (expanded);
// }

static char *expand_variable(char *str, t_data *data)
{
    char    *expanded;
    char    **cut_list;
    char    **exp_list;
    bool    first_exp;
    int     i;
    int     count;
    size_t  len;

    // Special case: string is exactly "$"
    if (o_ft_strncmp(str, "$", 2) == 0)
        return (ft_strdup("$"));

    cut_list = ft_split(str, '$');
    if (!cut_list)
        return (NULL);

    // Count how many parts
    count = 0;
    while (cut_list[count])
        count++;

    // Allocate exp_list
    exp_list = malloc(sizeof(char *) * (count + 2)); // +1 for possible trailing $
    if (!exp_list)
        return (free_argv(cut_list), NULL);

    first_exp = (str[0] == '$');
    i = 0;
    while (cut_list[i])
    {
        if (i == 0 && !first_exp)
            exp_list[i] = ft_strdup(cut_list[i]);
        else if (cut_list[i][0] == '\0') // just "$"
            exp_list[i] = ft_strdup("$");
        else
        {
            char *val = find_in_env(data->env, cut_list[i]);
            exp_list[i] = val ? val : ft_strdup("");
        }
        i++;
    }

    // Check if original ends in $
    len = o_ft_strlen(str);
    if (len > 0 && str[len - 1] == '$')
    {
        exp_list[i] = ft_strdup("$");  // preserve literal trailing $
        i++;
    }

    exp_list[i] = NULL;

    free_argv(cut_list);
    expanded = list_to_string(exp_list);
    free_argv(exp_list);
    return (expanded);
}



// entry function 
void expand_env_variables(t_tree *node, t_data *data)
{
    int i;

    i = 0;
    if (!node)
        return ;
    while (node->argv[i])
    {
        if (is_expandable(node->argv[i]))
            node->argv[i] = expand_variable(node->argv[i], data);
        i++;
    }
}


    // loop throught the argvector 
    // detect $
    // pass through quotetrimmer
    // launch pocket insertion algorithm 
    // ----> inser the new expaned string using the environment 
    //      if env returns NULL: do nothing to the $string
    //      else expand and pocket insert
    //      return new pointer to an expanded string
    //      and free old one