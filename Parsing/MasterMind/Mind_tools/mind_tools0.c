#include "../../minishell.h"

static int free_conditions(t_token *curr, t_token *temp, t_token **reserve)
{
    if (!curr->next)
    {
        printf("token free >> %s\n", curr->identity);
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
        // free(curr->identity);
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
        || curr->tok == RED_IN_ID || curr->tok == RED_OUT_ID || curr->tok == HERE_DOC_ID)
            return (0);
    return (1);
}

static void    join_till_end(t_token *curr, t_token *id_class)
{
    char *joined;

    joined = NULL;
    while (id_class != NULL)
    {
        // if (!conditions(id_class)) // u can send here the next id class, and check for the bug using this case cat'ls'nadi | pwd
        // {
        //     id_class->end = true;
        //     break ;
        // }
        joined = ft_strjoin(curr->identity, id_class->identity);
        free(curr->identity); // Might delete later (MindAllocator)
        curr->identity = joined;
        if (id_class->next && id_class->next->tok != STRING_ID
            || id_class->space_next == true)
        {
            id_class->end = true;
            break ;
        }
        id_class = id_class->next;
    }
}

void    joining_system(t_token *id_class)
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
            join_till_end(curr, curr->next);
            curr->next = free_till_end(curr->next);
        }
        curr = curr->next;
    }
    // debbuger_tk(id_class);
}
