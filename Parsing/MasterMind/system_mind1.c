#include "../minishell.h"

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
        if (!curr->next)
        {
            curr->end = false;
            free(temp);
            break;
        }
        else if (curr->end == true)
        {
            reserve = temp->next;
            curr->end = false;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    return (reserve);
}

static void    join_till_end(t_token *curr, t_token *id_class)
{
    char *joined;

    joined = NULL;
    while (id_class != NULL
            && id_class->tok == ARG_ID)
    {
        joined = ft_strjoin(curr->identity, id_class->identity);
        free(curr->identity); // Might delete later (MindAllocator)
        curr->identity = joined;
        if (id_class->next == NULL
                || id_class->space_next == true || id_class->tok == PIPE_ID
                || id_class->tok == AND_ID || id_class->tok == OR_ID
                || id_class->tok == ARG_ID)
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
        if (curr->tok == COMMAND_ID
            && curr->space_next == false && curr->next)
        {
            join_till_end(curr, curr->next);
            curr->next = free_till_end(curr->next);
        }
        curr = curr->next;
    }
    debbuger_tk(id_class);
}

// Master@Mindv1.1> cat'ls'nadi
// temp > ls
// reserve> nadi
// RE_identity> catls
// ID-> COMMAND_ID
// ****************
// RE_identity> nadi
// ID-> ARG_ID
// ****************
/*
    u can change the conditions in the join till the end into , 
        if (id_class->next == NULL
                || id_class->space_next == true)
        {
            if (id_class->net)
                id_class->end = true;
            break ;
        }
    and debbug this, cuz there is another behavior i cannot figure out, just run the same command
*/