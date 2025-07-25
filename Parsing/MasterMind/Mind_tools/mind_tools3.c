#include "../../minishell.h"

int algo(t_token *curr, t_token **op_field, t_token *in, t_token **yard)
{
    in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
    if (!in || !algorithm_options(curr, op_field, yard, in))
        return (S);
    return (F);
}

int add_op(t_token *curr, t_token **op_field, t_token **yard, t_token *in)
{
    in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
    if (!in)
        return (S);
    add_front_identity(op_field, in);
    return (F);
}

int add_n_remove(t_token *curr, t_token **op_field, t_token **yard, t_token *in)
{
    in = add_identity(ft_strdup(curr->identity), curr->tok, INIT, curr);
    if (!in)
        return (S);
    add_front_identity(op_field, in);
    if (!remove_op(yard, op_field, return_op(*op_field)))
        return (S);
    return (F);
}
