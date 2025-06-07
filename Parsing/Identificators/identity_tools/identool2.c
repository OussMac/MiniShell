#include "../../minishell.h"

int brace_len(char *input)
{
    int i;
    int len;
    int quote_state;

    i = 0;
    len = 0;
    quote_state = 0;
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
            quote_state += 1;
        if (quote_state % 2 == 0)
            quote_state = 0;
        if ((input[i] == '(' || input[i] == ')') && !quote_state)
            len++;
        i++;
    }
    return (len);
}

// Can the brace quote system be broken?
/*
    ("ls && "ls)", broken in this case, yet protected by the quotes (SEF)
*/

char *get_all_braces(char *input, t_brace_t *br)
{
    int i;
    int y;
    char *braces;

    i = 0;
    y = 0;
    braces = malloc(brace_len(input) + 1);
    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '\"')
            br->quote_state += 1;
        if (br->quote_state % 2 == 0)
            br->quote_state = 0;
        if ((input[i] == '(' || input[i] == ')') && !br->quote_state)
        {
            braces[y] = input[i];
            y++;
        }
        if (input[i] == '\0')
            break ;
        i++;
    }
    braces[y] = '\0';
    return (braces);
}

int realtp_braces(char *braces, int i, t_brace_t *br)
{
    if (braces[i] == ')' && !br->brace_op)
    {
        print_error(BRACE_ERR, NULL, 0);
        return (0);
    }
    else if (braces[i] == '(')
        br->brace_op++;
    else if (braces[i] == ')')
        br->brace_cl++;
    if (braces[i] == ')' && braces[i + 1] == '('
        && braces[i + 2] != ')')
    {
        print_error(BRACE_ERR, NULL, 0);
        return (0);
    }
    return (1);
}

int realt_braces(char *braces, t_brace_t *br)
{
    int i;

    i = 0;
    while (braces[i])
    {
        if (!realtp_braces(braces, i, br))
            return (0);
            // exit_status
        i++;
    }
    if (br->brace_cl != br->brace_op)
    {
        print_error(BRACE_ERR, NULL, 0);
        // exit_status
        return (0);
    }
    return (1);
}

char *scrap_braces(char *input, int *index, char *brace)
{
    int len;
    char *braces;
    t_brace_t br_tool;

    if (!realt_quotes(input, '\'', QUOTES_ERR)
        || !realt_quotes(input, '\"', QUOTES_ERR))
        return (NULL);
    ft_bzero(&br_tool, sizeof(t_brace_t));
    braces = get_all_braces(input, &br_tool);
    if (!braces)
        return(NULL);
    if (!realt_braces(braces, &br_tool))
        return (NULL);
    len = get_len(brace);
    while (len--)
        (*index)--;
    (*index)++;
    return (brace);
}
