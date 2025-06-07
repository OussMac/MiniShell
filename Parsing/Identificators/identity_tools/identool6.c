#include "../../minishell.h"

// int delimiter_next(t_token *next_heredoc, t_data *data)
// {
//     char *del_join;

//     if (next_heredoc->next && next_heredoc->space_next == false)
//     {
//         takeoff_quotes(next_heredoc);
//         takeoff_quotes(next_heredoc->next);
//         printf("del %s, del next %s\n", next_heredoc->identity, next_heredoc->next->identity);
//         del_join = ft_strjoin(next_heredoc->identity,
//         next_heredoc->next->identity);
//         free(next_heredoc->identity);
//         next_heredoc->identity = del_join;
//         free(next_heredoc->next->identity);
//         next_heredoc->tok = DEL_ID;
//         next_heredoc->next = NULL;
//         return(1);
//     }
//     return(0);
// }

// static void set_free(t_token *curr)
// {
//     int i;

//     i = list_size(curr);
//     while(i > 0)
//     {
        
//     }
// }

static char *join_delimiter(char *del_join, t_token *delimiter)
{
    int i;
    char *del;
    char *tmp;

    i = 0;
    del = malloc(get_len(delimiter->identity) + 1);
    while (delimiter->identity[i])
    {
        del[i] = delimiter->identity[i];
        i++;
    }
    del[i] = '\0';
    tmp = ft_strdup(del_join);
    free(del_join);
    del_join = ft_strjoin(tmp, del);
    free(del);
    return (del_join);
}

int delimiter_next(t_token *next_heredoc, t_data *data)
{
    char *del_join;
    t_token *delimiter;

    del_join = NULL;
    delimiter = next_heredoc;
    if (next_heredoc->next == NULL
            || next_heredoc->space_next == true)
        return(0);
    while (next_heredoc)
    {
        takeoff_quotes(next_heredoc);
        del_join = join_delimiter(del_join, next_heredoc);
        if (next_heredoc->space_next == false)
            break;
        next_heredoc = next_heredoc->next;
    }
    return(1);
}
/*
    seems good, next to do, is to free all nodes that has beeng extracted
    as delimiters for heredoc, and joined on the first delimiter node, 
    free them from the first point to the null or to the space next true node, 
    in the case of null its fine, in the case of space next true, we need to link
    the first delimiter node, with the next space true node, inchallah, do that
    at home, Good luck inchallah
*/