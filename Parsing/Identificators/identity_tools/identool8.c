#include "../../minishell.h"

void    get_quotes_state(t_token *delimiter)
{
    t_token *curr;
    t_token *head;

    curr = delimiter;
    head = delimiter;
    while (curr != NULL)
    {
        if (curr->was_double_quote == 1)
        {
            head->was_double_quote = 1;
            break ;
        }
        else if (curr->was_single_quote == 1)
        {
            head->was_single_quote = 1;
            break ;
        }
        curr = curr->next;
    }
}