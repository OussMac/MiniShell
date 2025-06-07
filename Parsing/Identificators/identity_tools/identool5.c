#include "../../minishell.h"

void takeoff_quotes(t_token *tok)
{
    char *no_quotes;
    if (tok->tok == S_QUOTE_ID)
    {
        no_quotes = ft_strtrim(tok->identity, "\'");
        free(tok->identity);
        tok->identity = no_quotes;
        tok->was_single_quote = 1;
    }
    else if (tok->tok == D_QUOTE_ID)
    {
        no_quotes = ft_strtrim(tok->identity, "\"");
        free(tok->identity);
        tok->identity = no_quotes;
        tok->was_double_quote = 1;
    }
}

int change_id(t_token *next_heredoc, t_data *data)
{
    if (delimiter_next(next_heredoc, data))
        return(1);
    if (next_heredoc->op)
    {
        syntax_error_found(next_heredoc, data);
        return(0);
    }
    takeoff_quotes(next_heredoc);
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

int printer(t_token *curr)
{
    while(curr)
    {
        printf("printer > %s\n", curr->identity);
        curr = curr->next;
    }
    return(1);
}

int requirements(t_token *curr, t_token *id_class, t_data *data)
{
    if (curr->next == NULL)
        return (0);
    else if (curr->tok == HERE_DOC_ID
        && !curr->here_done && get_here_times(id_class) == 1)
    {
            data->here_case = 2;
            return (1);
    }
    return (0);
}