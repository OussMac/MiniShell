#include "../../minishell.h"

int realt_quotes(char *input, int doubles_case, int index, char *err)
{
    int doubles;

    doubles = 0;
    if (!ft_strchr(input, doubles_case))
        return (1);
    while (input[index])
    {
        if (input[index] == doubles_case
            && doubles == 1)
        {
            doubles++;
            break;
        }
        if (input[index] == doubles_case)
            doubles++;
        index++;
    }
    if (doubles % 2 != 0)
    {
        // exit status
        print_error(err, NULL, 0);
        return (0);
    }
    return (1);
}

void space_flag(t_token *id_class)
{
    t_token *last_token;

    last_token = ft_lstlast(id_class);
    if (id_class)
        last_token->space_next = true;
}

int all_whitespaces(char x)
{
    if ((9 <= x && x <= 13) || x == 32)
            return (0);
    return (1);
}

int unit_call_here_doc(t_token **id_class, char *input, t_data *data)
{
    if (!here_doc_check(*id_class, data))
    {
        *id_class = NULL;
        return (0);
    }
    return (1);
}

void unit_call_space_next(t_token *id_class, char *input, int *index)
{
    if (!all_whitespaces(input[*index]))
    {
        space_flag(id_class);
        (*index)++;
    }
}