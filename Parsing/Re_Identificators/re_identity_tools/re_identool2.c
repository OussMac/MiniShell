#include "../../minishell.h"

static t_token *get_argument(t_token *id_class)
{
    while (id_class != NULL)
    {
        if (id_class->op_case)
            return (NULL);
        if ((id_class->tok == ARG_ID && id_class->marked == false))
        {
            id_class->marked = true;
            return (id_class);
        }
        id_class = id_class->next;
    }
    return (NULL);
}

static void delete_args(t_token *id_class)
{
    t_token *temp;
    t_token *curr;
    t_token *before;

    before = NULL;
    curr = id_class;
    while (curr != NULL)
    {
        if (curr->tok == ARG_ID && curr->marked == true)
        {
            before->next = curr->next;
            curr->marked = false;
            free(curr->identity);
            free(curr);
            break ;
        }
        before = curr;
        curr = curr->next;
    }
}

static int operations(char *temp, t_token *temp2, t_token *curr)
{
    char *hold;

    temp = ft_strjoin(curr->identity, " ");
    temp2 = get_argument(curr);
    if (temp2)
    {
        hold = curr->identity;
        curr->identity = ft_strjoin(temp, temp2->identity);
        if (!curr->identity)
            return (0);
        free(hold);
    }
    return (free(temp), 1);
}

int arg_system(t_token *id_class)
{
    char *temp;
    t_token *temp2;
    t_token *curr;

    curr = id_class;
    while (curr != NULL)
    {
        if (curr->tok == COMMAND_ID)
        {
            if (!operations(temp, temp2, curr))
                return (0);
        }
        delete_args(id_class);
        if (curr->next && curr->next->tok == ARG_ID)
            continue;
        curr = curr->next;
    }
    return (1);
}
