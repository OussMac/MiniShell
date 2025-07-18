#include "../minishell.h"

static t_token *extract_list(t_token *id_class, t_data *data)
{
    int i;
    t_token *id;
    t_token *extract;

    i = 0;
    id = NULL;
    extract = NULL;
    while (id_class != NULL)
    {
        if (id_class->tok == HERE_DOC_ID
            || ((id_class->tok == PIPE_ID || id_class->tok == AND_ID
                    || id_class->tok == OR_ID)
                && id_class->next->tok == HERE_DOC_ID && i != 0))
            break;
        id = add_identity(ft_strdup(id_class->identity), id_class->tok, D_INIT, NULL);
        if (!id)
        {
            data->fail = 1;
            return (NULL);
        }
        add_back_identity(&extract, id, D_INIT);
        id_class = id_class->next;
        i++;
    }
    return (extract);
}

int sef_doc(t_token *id_class, t_data *data, t_brace_t *br)
{
    t_token *class;
    t_token *new_class;

    new_class = extract_list(id_class, data);
    if (!new_class && data->fail == 1)
        return (0);
    else if (!new_class && data->fail == 0)
        return(1);
    set_ops(new_class);
    if (!syntax_verify(new_class, data, br))
    {
        list_cleaner(&new_class);
        return (0);
    }
    list_cleaner(&new_class);
    return (1);
}

void    clean_stacks(t_token **stackone, t_token **stacktwo)
{
    list_cleaner(stackone);
    list_cleaner(stacktwo);
}