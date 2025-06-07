#include "../../minishell.h"

int change_id(t_token *next_heredoc, t_data *data)
{
    char *no_quotes;

    if (next_heredoc->op)
    {
        syntax_error_found(next_heredoc, data);
        return(0);
    }
    if (next_heredoc->tok == S_QUOTE_ID)
    {
        no_quotes = ft_strtrim(next_heredoc->identity, "\'");
        free(next_heredoc->identity);
        next_heredoc->identity = no_quotes;
        next_heredoc->was_single_quote = 1;
    }
    else if (next_heredoc->tok == D_QUOTE_ID)
    {
        no_quotes = ft_strtrim(next_heredoc->identity, "\"");
        free(next_heredoc->identity);
        next_heredoc->identity = no_quotes;
        next_heredoc->was_double_quote = 1;
    }
    next_heredoc->tok = DEL_ID;
    return (1);
}

char *get_delimiter(t_token *token)
{
    t_token *curr;
    
    curr = token;
    while (curr != NULL)
    {
        if (curr->tok == DEL_ID)
            return (curr->identity);
        curr = curr->next;
    }
    return (NULL);
}

int get_here_times(t_token *id_class)
{
    t_token *curr;

    curr = id_class;
    while (curr != NULL)
    {
        if (curr->tok == HERE_DOC_ID
            && !curr->here_done)
        {
            curr->here_done = 1;
            return (curr->here_times);
        }
        curr = curr->next;
    }
    return (0);
}
