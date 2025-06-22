#include "../../minishell.h"

t_token *get_all_braces(t_token *token)
{
    t_token *in;
    t_token *braces;

    braces = NULL;
    while (token != NULL)
    {
        if (token->tok == BRACE_O_ID || token->tok == BRACE_C_ID)
        {
            in = add_identity(token->identity, token->tok, D_INIT, NULL);
            add_back_identity(&braces, in, D_INIT);
        }
        token = token->next;
    }
    set_ops(braces);
    return (braces);
}

static void pop_out_brace(t_token **token)
{
    t_token *reserve;

    if ((*token)->next != NULL)
    {
        reserve = (*token)->next;
        free((*token)->identity);
        free((*token));
        (*token) = reserve;
    }
    else
    {
        free((*token)->identity);
        free((*token));
        (*token) = NULL;
    }
}

int push_br(t_token **stack_br, t_token *to_push)
{
    t_token *new;

    new = add_identity(to_push->identity, to_push->tok, D_INIT, NULL);
    // new to be freed each time and not to be included in MindAllocator :)
    if (new->tok == BRACE_C_ID && !*stack_br)
        return (0);
    else if (new->tok == BRACE_C_ID && (*stack_br)->tok == BRACE_O_ID)
        pop_out_brace(stack_br);
    else
        add_back_identity(stack_br, new, D_INIT);
    return (1);
}