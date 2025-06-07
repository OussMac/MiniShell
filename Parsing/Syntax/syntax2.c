#include "../minishell.h"

static int scan_for_doubles(t_token *token)
{
    t_token *curr;

    curr = token;
    while (curr != NULL)
    {
        if (curr->tok == BRACE_O_ID)
            return (1);
        curr = curr->next;
    }
    return(0);
}

static int non_print(char *in)
{
    int i;

    i = 0;
    while (in[i])
    {
        if ((0 <= in[i] && in[i] <= 32)
            || in[i] == 127)
                return (0);
        i++;
    }
    return (1);
}

static void in_alert(t_token *token, int *flag_in)
{
    while (token != NULL)
    {
        if (token->tok == BRACE_C_ID)
            break ;
        if ((0 <= token->tok && token->tok <= 6)
                || (9 <= token->tok && token->tok <= 14))
            *flag_in = 1;
        token = token->next;
    }
}

int doubles_verify(t_token *token, t_data *data)
{
    int flag_in;
    t_token *curr;

    flag_in = 0;
    curr = token;
    if (!scan_for_doubles(token))
        return (1);
    while (curr != NULL
            && curr->next != NULL)
    {
        if (curr->tok == BRACE_O_ID)
        {
            in_alert(curr->next, &flag_in);
            if (!non_print(curr->next->identity) && !flag_in
                || (curr->tok == BRACE_O_ID
                        && curr->next->tok == BRACE_C_ID))
            {
                syntax_error_found(curr->next, data);
                return (0);
            }
        }
        curr = curr->next;
    }
    return (1);
}

/* ("ls && ls)" check this case and try to know why its was best to not scrap braces
    as we scrapped quotes*/

/*
    in the case of ( (ls))

    it deos not return an error because the in_alert function returns flag in with one
    cuz ls is there, even if non_print returns zero cuz space is found, it does
    not return (SEF)
*/