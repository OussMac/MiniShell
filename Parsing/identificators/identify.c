#include "../minishell.h"

int set_ops(t_token *id_class)
{
    while (id_class != NULL)
    {
        if (0 <= id_class->tok && id_class->tok <= 6)
            id_class->op = 1;
        else
            id_class->op = 0;
        if (id_class->tok == RED_OUT_ID || id_class->tok == RED_IN_ID
            || id_class->tok == HERE_DOC_ID || id_class->tok == RED_APP_ID
            || id_class->tok == BRACE_O_ID || id_class->tok == BRACE_C_ID)
            id_class->firsts = 1;
        else
            id_class->firsts = 0;
        if (id_class->tok == BRACE_C_ID || id_class->tok == BRACE_O_ID)
            id_class->br = 1;
        else
            id_class->br = 0;
        if (id_class->tok == PIPE_ID || id_class->tok == OR_ID
                || id_class->tok == AND_ID)
            id_class->op_case = 1;
        else
            id_class->op_case = 0;
        id_class = id_class->next;
    }
    return (1);
}

int identity_scraping(char *ident, enum grammar en,
        t_token *id, t_token **id_class)
{
    if (!ident)
        return (0);
    id = add_identity(ident, en, D_INIT, NULL);
    if (!id)
        list_cleaner(id_class);
    add_back_identity(id_class, id, INIT);
    return (1);
}

static int unification(char *input, int *i, t_token *id, t_token **id_class)
{
    first_unit(input, i, id, id_class);
    sec_unit(input, i, id, id_class);
    third_unit(input, i, id, id_class);
    if (!forth_unit(input, i, id, id_class)
        || !set_ops(*id_class))
    {
        list_cleaner(id_class);
        *id_class = NULL;
        return (0);
    }
    set_ops(*id_class);
    return (1);
}

t_token *get_identity(char *input, t_data *data, t_brace_t *br)
{
    int i;
    t_token *id;
    t_token *id_class;

    i = 0;
    id = NULL;
    id_class = NULL;
    while (input[i])
    {
        if (!unification(input, &i, id, &id_class))
            break ;
        if (all_whitespaces(input[i]) && input[i] != '\0')
            continue ;
        if (!unit_call_here_doc(&id_class, input, data, br))
            break ;
        unit_call_space_next(id_class, input, &i);
    }
    if (!syntax_verify(id_class, data, br))
    {
        list_cleaner(&id_class);
        id_class = NULL;
    }
    free(input);
    return (id_class);
}
