#include "../../minishell.h"

t_token *return_op(t_token *op_field)
{
    while (op_field != NULL)
    {
        if (op_field->op_case)
            return (op_field);
        op_field = op_field->next;
    }
    return (NULL);
}

void    set_power(t_token *id_class)
{
    while (id_class != NULL)
    {
        if (id_class->tok == PIPE_ID)
            id_class->power = H_POW;
        else if (id_class->tok == AND_ID)
            id_class->power = M_POW;
        else if (id_class->tok == OR_ID)
            id_class->power = L_POW;
        id_class = id_class->next;
    }
}

void    set_end(t_token **op_field)
{
    t_token *temp;
    t_token *curr;
    t_token *reserve;

    temp = NULL;
    reserve = NULL;
    curr = *op_field;
    while (curr != NULL)
    {
        free(curr->identity);
        free(temp);
        temp = curr;
        if (curr->next == NULL)
        {
            free(temp);
            break;
        }
        else if (curr->end == true)
        {
            if (curr->next)
                reserve = curr->next;
            curr->end = false;
            free(temp);
            break;
        }
        curr = curr->next;
    }
    (*op_field) = reserve;
}

int mark_ending(t_token *op_field, t_token **yard)
{
    int x;

    x = 0;
    while (op_field != NULL)
    {
        if (op_field->op_case && x == 0)
        {
            if (!add_token(op_field, yard))
                return (S);
        }
        if (op_field->tok == BRACE_O_ID)
        {
            x = 1;
            op_field->end = true;
            break ;
        }
        op_field = op_field->next;
    }
    return (F);
}
