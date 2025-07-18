#include "../../minishell.h"

static int free_conditions(t_token *curr, t_token *temp, t_token **reserve)
{
    if (!curr->next)
    {
        curr->end = false;
        free(temp);
        return (0);
    }
    else if (curr->end == true)
    {
        *reserve = temp->next;
        curr->end = false;
        free(temp);
        return (0);
    }
    return(1);
}

static t_token *free_till_end(t_token *curr)
{
    t_token *temp;
    t_token *reserve;

    temp = NULL;
    reserve = NULL;
    while (curr != NULL)
    {
        free(curr->identity);
        free(temp);
        temp = curr;
        if (!free_conditions(curr, temp, &reserve))
            break;
        curr = curr->next;
    }
    return (reserve);
}

int    conditions(t_token *curr)
{
    if (curr->tok == PIPE_ID
        || curr->tok == OR_ID || curr->tok == AND_ID || curr->tok == RED_APP_ID
        || curr->tok == RED_IN_ID || curr->tok == RED_OUT_ID || curr->tok == HERE_DOC_ID
        || curr->br)
            return (0);
    return (1);
}

static int    join_till_end(t_token *curr, t_token *id_class)
{
    char *joined;

    joined = NULL;
    while (id_class != NULL)
    {
        joined = ft_strjoin(curr->identity, id_class->identity);
        if (!joined)
            return (S);
        free(curr->identity);
        curr->identity = joined;
        if (id_class->next && id_class->next->tok != STRING_ID
            || id_class->space_next == true)
        {
            id_class->end = true;
            break ;
        }
        id_class = id_class->next;
    }
    return (F);
}

int    joining_system(t_token *id_class)
{
    char *joined;
    t_token *curr;

    curr = id_class;
    joined = NULL;
    while (curr != NULL)
    {
        if (curr->tok == STRING_ID
            && curr->space_next == false && curr->next
            && conditions(curr->next))
        {
            if (!join_till_end(curr, curr->next))
                return (S);
            curr->next = free_till_end(curr->next);
        }
        curr = curr->next;
    }
    return (F);
}
