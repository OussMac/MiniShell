#include "../minishell.h"

static void scan_for_doubles(t_token *token)
{
    t_token *curr;

    curr = token;
    while (curr != NULL)
    {
        if (curr->tok == BRACE_O_ID || curr->tok == BRACE_C_ID)
            curr->brace = 1;
        else if (curr->tok == S_QUOTE_ID)
            curr->s_quotes = 1;
        else if (curr->tok == D_QUOTE_ID)
            curr->d_quotes = 1;
        curr = curr->next;
    }
}

static int brace_verification(t_token *token, t_data *data)
{
    t_token *curr;
    int op_brace;
    int cl_brace;

    op_brace = 0;
    cl_brace = 0;
    curr = token;
    while (curr != NULL)
    {
        if (cl_brace > 0 && op_brace == 0)
        {
            print_error(CL_BEFORE, NULL, 0);
            //MindAllocator
            data->exit_status = 2;
            return (F);
        }
        if (curr->tok == BRACE_O_ID)
            op_brace++;
        else if (curr->tok == BRACE_C_ID)
            cl_brace++;
        curr = curr->next;
    }
    if (op_brace != cl_brace)
    {
        print_error(BRACE_ERR, NULL, NL);
        //MindAllocator
        data->exit_status = 2;
        return (F);
    }
    return (S);
}

static int quotes_number(char *str, char qt)
{
    int i;
    int type_count;

    i = 0;
    type_count = 0;
    while (str[i])
    {
        if (str[i] == qt)
            type_count++;
        i++;
    }
    if (type_count % 2 != 0)
        return (F);
    return (S);
}

static int quotes_verification(t_token *token, int type, t_data *data)
{
    int type_count;
    t_token *curr;

    curr = token;
    type_count = 0;
    while (curr != NULL)
    {
        if(curr->tok == type)
        {
            if ((type == S_QUOTE_ID
                && quotes_number(curr->identity, S_QUOTE))
                || (type == D_QUOTE_ID
                && quotes_number(curr->identity, D_QUOTE)))
            {
                print_error(QUOTES_ERR, NULL, 0);
                data->exit_status = 2;
                return(F);
            }
        }
        curr = curr->next;
    }
    return (S);
}

void doubles_verify(t_token *token, t_data *data)
{
    t_token *curr;

    curr = token;
    scan_for_doubles(token);
    while (curr != NULL)
    {
        if (curr->s_quotes
            && quotes_verification(token, ONE_QUOTE, data))
            return ;
        if (curr->d_quotes
            && quotes_verification(token, DUO_QUOTE, data))
            return ;
        if (curr->brace 
            && brace_verification(token, data))
            return ;
        curr = curr->next;
    }
}

/* ("ls && ls)" check this case and try to know why its was best to not scrap braces
    as we scrapped quotes*/