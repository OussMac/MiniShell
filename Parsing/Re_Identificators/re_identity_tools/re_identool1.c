#include "../../minishell.h"

t_token *re_builder(t_token *id_class)
{
    t_token *in;
    t_token *curr;
    t_token *re_built;

    re_built = NULL;
    curr = id_class;
    while (curr != NULL)
    {
        if (!(1 <= curr->tok
                && curr->tok <= 3))
        {
            in = add_identity(curr->identity, curr->tok, INIT, curr);
            add_back_identity(&re_built, in, D_INIT);
        }
        curr = curr->next;
    }
    return (re_built);
}

// ls >> out < infile -l