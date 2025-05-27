#include "../minishell.h"

static void syntax_error_found(t_token *curr, t_data *data)
{
    print_error(SYNTAX, curr->identity, SYN);
    data->exit_status = 1;
}

static int first_and_null(t_token *curr)
{
    if (curr->op && !curr->next)
        return (F);
    if (curr->op && !curr->firsts)
        return (F);
    else if (curr->op && curr->firsts
        && curr->next && curr->next->tok == SPACE_ID
        && curr->next->next == NULL)
        return (F);
    return (S);
}

static int hold_and_check(t_token *hold, t_token *curr)
{
    if ((hold->op && curr->op))
    return (F);
    if ((curr->op && !curr->next)
    || (curr->op && curr->next && curr->next->tok == SPACE_ID
        && !curr->next->next))
        return (F);
    return (S);
}
    
static int cmp_nodes(t_token *hold, t_token *verify, t_data *data)
{
    if (hold_and_check(hold, verify))
    {
            syntax_error_found(verify, data);
            //MindAllocator
            data->exit_status = 2;
            return(F);
    }
    return(S);
}

void syntax_verify(t_token *token, t_data *data)
{
    int i;
    t_token *hold;
    t_token *verify;
    t_token *first;

    i = 0;
    hold = NULL;
    verify = token;
    first = token;
    while (verify != NULL)
    {
        if (verify->tok == SPACE_ID && verify->next)
            verify = verify->next;
        if (hold != NULL
            && cmp_nodes(hold, verify, data))
            return ;
        if (i == 0 && first_and_null(verify))
        {
                syntax_error_found(verify, data);
                //MindAllocator
                data->exit_status = 2;
                return ;
        }
        hold = verify;
        verify = verify->next;
        i++;
    }
    doubles_verify(token, data);
}
