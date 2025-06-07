#include "../minishell.h"

static int set_ops(t_token *id_class)
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
    id = add_identity(ident, en);
    add_back_identity(id_class, id);
    return (1);
}

t_token *get_identity(char *input, t_data *data)
{
    int i;
    t_token *id;
    t_token *id_class;

    i = 0;
    id = NULL;
    id_class = NULL; // why seggev??
    while (input[i])
    {
        first_unit(input, &i, id, &id_class);
        sec_unit(input, &i, id, &id_class);
        third_unit(input, &i, id, &id_class);
        if (!forth_unit(input, &i, id, &id_class)
        || !set_ops(id_class) || (!here_doc_check(id_class, data)))
        {
            id_class = NULL;
            //MindAllocator
            break;
        }
        i++;
    }
    if (!syntax_verify(id_class, data))
    {
        printf("Second SEF Check\n");
        id_class = NULL;
    }
    // debbuger_tk(id_class);
    // MindAllocator
    return (id_class);
}

/*Master@Mindv1.0> ("ls && ls)"
MasterMind: Invalid Use Of Braces
identity> (
ID-> BRACE_O_ID
****************
identity> "ls && ls)"
ID-> D_QUOTE_ID
****************
Master@Mindv1.0> ("ls && ls)")
MasterMind: Invalid Use Of Braces
Master@Mindv1.0> */