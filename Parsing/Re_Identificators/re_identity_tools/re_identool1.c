#include "../../minishell.h"

static int no_command(t_token *id_class)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (id_class != NULL)
    {
        if (id_class->tok == COMMAND_ID)
            x = 1;
        if (red_checks(id_class))
            y = 1;
        id_class = id_class->next;
    }
    if (x + y > 1)
        return (1);
    return (0);
}

t_token *re_builder(t_token *id_class)
{
    t_token *in;
    t_token *curr;
    t_token *re_built;

    re_built = NULL;
    curr = id_class;
    // debbuger_tk(id_class);
    while (curr != NULL)
    {
        if (!(1 <= curr->tok && curr->tok <= 4))
        {
            in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
            if (!in)
                return (clean_fd(re_built), list_cleaner(&re_built), NULL);
            add_back_identity(&re_built, in, D_INIT);
        }
        curr = curr->next;
    }
    if (no_command(re_built))
    {
        command_ahead(re_built);
        red_system(&re_built);
    }
    list_cleaner(&id_class);
    // debbuger_tk(re_built);
    return (re_built);
}
