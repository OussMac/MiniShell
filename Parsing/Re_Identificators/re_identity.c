#include "../minishell.h"

static void remove_q(t_token *curr, int mode)
{
    char *removed;

    if (mode == SQ)
    {
        removed = ft_strtrim(curr->identity, "\'");
        free(curr->identity);
        curr->identity = removed;
        curr->was_single_quote = 1;
    }
    else if (mode == DQ)
    {
        removed = ft_strtrim(curr->identity, "\"");
        free(curr->identity);
        curr->identity = removed;
        curr->was_double_quote = 1;
    }
    curr->tok = STRING_ID;
}

static void quotes_removal(t_token *id_class)
{
    t_token *curr;

    curr = id_class;
    while (curr != NULL)
    {
        if (curr->tok == S_QUOTE_ID)
            remove_q(curr, SQ);
        else if (curr->tok == D_QUOTE_ID)
            remove_q(curr, DQ);
        curr = curr->next;
    }
}

t_token    *re_identity(t_token *id_class)
{
    int string;
    t_token *curr;

    string = 0;
    curr = id_class;
    quotes_removal(id_class);
    while (curr != NULL)
    {
        if (curr->tok == PIPE_ID || curr->tok == OR_ID
                || curr->tok == AND_ID)
            string = 0;
        re_identifications(curr, &string);
        cmd_arg(&curr, &string);
        curr = curr->next;
    }
    // debbuger_tk(id_class);
    return (re_builder(id_class));
}
