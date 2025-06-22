#include "../../minishell.h"

void set_free(t_token *curr)
{
    t_token *temp;

    temp = NULL;
    while (curr)
    {
        free(curr->identity);
        free(temp);
        temp = curr;
        if (!curr->next)
        {
            free(temp);
            temp = NULL;
            break ;
        }
        curr = curr->next;
    }
}

static void free_nodes_del(t_token *delimiter, char *del_join)
{
    t_token *after_delimiter;

    free(delimiter->identity);
    delimiter->identity = del_join;
    delimiter->tok = DEL_ID;
    after_delimiter = delimiter->next;
    set_free(after_delimiter);
    delimiter->next = NULL;
}

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
        return (0);
    while (next_heredoc)
    {
        takeoff_quotes(next_heredoc);
        del_join = join_delimiter(del_join, next_heredoc);
        if (next_heredoc->space_next == true)
            break ;
        next_heredoc = next_heredoc->next;
    }
    free_nodes_del(delimiter, del_join);
    return (1);
}
/*
    seems good, next to do, is to free all nodes that has beeng extracted
    as delimiters for heredoc, and joined on the first delimiter node, 
    free them from the first point to the null or to the space next true node, 
    in the case of null its fine, in the case of space next true, we need to link
    the first delimiter node, with the next space true node, inchallah, do that
    at home, Good luck inchallah
*/