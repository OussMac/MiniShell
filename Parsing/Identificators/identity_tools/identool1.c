#include "../../minishell.h"

int len_of_string(char *input, int index)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while(input[i])
    {
        if (check_alpha(input[index], input[i + 1]))
            break;
        len++;
        i++;
    }
    return (len);
}

char *scrap_string(char *input, int *index)
{
    int i;
    char *scrap;
    
    i = 0;
    scrap = malloc(len_of_string(input, *index) + 1);
    if (!scrap)
        exit(EXIT_FAILURE);
    while (input[*index])
    {
        if (check_alpha(input[*index], input[*index + 1]))
            break;
        scrap[i] = input[*index];
        (*index)++;
        i++;
    }
    scrap[i] = '\0';
    return (scrap);
}

char *scrap(int *index, char *scrapped)
{
    int len;

    len = get_len(scrapped);
    while (len--)
        (*index)++;
    return(scrapped);
}

int len_of_quote(char *input, char quote_case, int index)
{
    int len;

    len = 0;
    while(input[index])
    {
        len++;
        index++;
        if (input[index] == quote_case)
        {
            len++;
            break ;
        }
    }
    return (len);
}

char *scrap_quote(char *input, int *index, int quote_case)
{
    int i;
    char *quote;

    i = 0;
    if (!realt_quotes(input, quote_case, *index, QUOTES_ERR))
        return (NULL);
    quote = malloc(len_of_quote(input, quote_case, *index) + 1);
    if (!quote)
        exit(EXIT_FAILURE);
    while (input[*index])
    {
        quote[i] = input[*index];
        i++;
        (*index)++;
        if (input[*index] == quote_case)
        {
            quote[i] = input[*index];
            (*index)++;
            i++;
            break ;
        }
    }
    quote[i] = '\0';
    return (quote);
}
