#include "../minishell.h"

static void add_token(t_token *curr, t_token **yard)
{
    t_token *in;

    in = add_identity(curr->identity, curr->tok, D_INIT, NULL);
    add_back_identity(yard, in, D_INIT);
}

static void operations_field(t_token *curr, t_token **op_field, t_token **yard)
{
    int brace;
    t_token *in;
    t_token *brace_op;

    brace = 0;
    in = NULL;
    if (curr->tok == BRACE_O_ID)
    {
        in = add_identity(curr->identity, curr->tok, D_INIT, NULL);
        add_front_identity(op_field, in);
        brace = 1;
    }
    else if (curr->tok == BRACE_C_ID && brace == 1)
        send_take_out(curr, op_field, yard); // function to pop out braces and operative to the yard (TODO)
}

t_token *shunting_yard_algorithm(t_token *id_class)
{
    t_token *curr;
    t_token *yard;
    t_token *op_field;

    yard = NULL;
    op_field = NULL;
    curr = id_class;
    while (curr != NULL)
    {
        if (curr->tok == COMMAND_ID || curr->tok == ARG_ID)
            add_token(curr, &yard);
        else if (curr->op_case || curr->br)
            operations_field(curr, &op_field, &yard);
        curr = curr->next;
    }
}