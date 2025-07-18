#include "../minishell.h"

void    first_unit(char *input, int *i, t_token *id, t_token **id_class)
{
    if (!check_alpha(input[*i], input[*i + 1]))
         identity_scraping(scrap_string(input, i),
             STRING_ID, id, id_class);
    else if (input[*i] == PIPE
         && !check_doubles(input[*i] , input[*i + 1]))
        identity_scraping(scrap(i, "|"),
        PIPE_ID, id, id_class);
}

void    sec_unit(char *input, int *i, t_token *id, t_token **id_class)
{
    if (input[*i] == OR
        && check_doubles(input[*i] , input[*i + 1]))
        identity_scraping(scrap(i, "||"),
        OR_ID, id, id_class);
    else if (input[*i] == RED_OUT
        && !check_doubles(input[*i], input[*i + 1]))
        identity_scraping(scrap(i, ">"),
        RED_OUT_ID, id, id_class);
    else if (input[*i] == RED_APP
        && check_doubles(input[*i] , input[*i + 1]))
        identity_scraping(scrap(i, ">>"),
        RED_APP_ID, id, id_class);
}

void    third_unit(char *input, int *i, t_token *id, t_token **id_class)
{
    if (input[*i] == AND
        && check_doubles(input[*i], input[*i + 1]))
        identity_scraping(scrap(i, "&&"),
        AND_ID, id, id_class);
    else if (input[*i] == RED_IN
        && !check_doubles(input[*i], input[*i + 1]))
        identity_scraping(scrap(i, "<"),
        RED_IN_ID, id, id_class);
    else if (input[*i] == HERE_DOC
        && check_doubles(input[*i], input[*i + 1]))
        identity_scraping(scrap(i, "<<"),
        HERE_DOC_ID, id, id_class);
}


int    forth_unit(char *input, int *i, t_token *id, t_token **id_class)
{
    if (input[*i] == S_QUOTE)
    {
        if (!identity_scraping(scrap_quote(input, i, S_QUOTE),
        S_QUOTE_ID, id, id_class))
            return (0);
    }
    else if (input[*i] == D_QUOTE)
    {
        if (!identity_scraping(scrap_quote(input, i, D_QUOTE),
        D_QUOTE_ID, id, id_class))
            return (0);
    }
    else if (input[*i] == BRACE_OP)
    {
        if (!identity_scraping(scrap_braces(input, i, "("),
        BRACE_O_ID, id, id_class))
            return(0);
    }
    else if (input[*i] == BRACE_CL)
    {
        if (!identity_scraping(scrap_braces(input, i, ")"),
        BRACE_C_ID, id, id_class))
            return(0);
    }
    return (1);  
}
