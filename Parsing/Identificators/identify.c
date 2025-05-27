#include "../minishell.h"

static void set_ops(t_token *id_class)
{
    t_token *curr;

    curr = id_class;
    while(curr != NULL)
    {
        if(0 <= curr->tok && curr->tok <= 6)
            curr->op = 1;
        else
            curr->op = 0;
        if (curr->tok == RED_OUT_ID || curr->tok == RED_IN_ID
            || curr->tok == HERE_DOC_ID || curr->tok == RED_APP_ID)
            curr->firsts = 1;
        else
            curr->firsts = 0;
        curr = curr->next;
    }
}

void identity_scraping(char *ident, enum grammar en,
        t_token *id, t_token **id_class)
{
    id = add_identity(ident, en);
    add_back_identity(id_class, id);
}

t_token *get_identity(char *input)
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
        forth_unit(input, &i, id, &id_class);
        i++;
    }
    set_ops(id_class);
    debbuger_tk(id_class);
    return (id_class);
}
