#include "../execute.h"

static bool is_expandable(char *str)
{
    int i;

    i = 0;
    while (str[i])
        if (str[i++] == '$')
            return (true);
    return (false);
}

static int	ft_isalnum(int c)
{
	if (c == '?' || (c <= '9' && c >= '0') || (c <= 'Z' && c >= 'A')
		|| (c <= 'z' && c >= 'a'))
	{
		return (1);
	}
	return (0);
}


static int  add_exp_token(t_exp_tokens **head, char *variable, bool in_sq, bool in_dq)
{
    t_exp_tokens    *new;
    t_exp_tokens    *curr;

    if (!head || !variable)
        return (EXIT_FAILURE);
    new = malloc(sizeof(t_exp_tokens));
    if (!new)
        return (EXIT_FAILURE);
    new->string = variable;
    new->is_env_var = is_expandable(variable);
    new->single_q = in_sq;
    new->double_q = in_dq;
    new->wrap_me = false;
    new->next = NULL;
    if (!*head)
        *head = new;
    else
    {
        curr = *head;
        while(curr->next)
            curr = curr->next;
        curr->next = new;
    }
    return (EXIT_SUCCESS);
}

void print_exp_list(t_exp_tokens *head)
{
    t_exp_tokens *curr;

    curr = head;
    while (curr)
    {
        printf("String: [%s], is_env_var: %d, single_q: %d, double_q: %d, wrap_me: %d\n",
               curr->string, curr->is_env_var, curr->single_q, curr->double_q , curr->wrap_me);
        curr = curr->next;
    }
}





t_exp_tokens *o_mini_parser(t_tree *node, t_data *data, char *str)
{
    int             start;
    int             end;
    int             i;
    bool            in_sq;
    bool            in_dq;
    t_exp_tokens    *exp_tokens;

    i = 0;
    in_sq = false;
    in_dq = false;
    exp_tokens = NULL;
    printf(RED" string to parse ==> [ .%s. ]"RST"\n", str);

    // main loop
    i = 0;
    while (str[i])
    {
        // skip unquoted spaces
        if (str[i] == ' ' && in_sq == false && in_dq == false)
        {
            i++;
            continue ;
        }

        // 🟩 [1] - if we hit single quote ' AND not in double quote ": literal string.
        if (str[i] == '\'' && in_dq == false)
        {
            if (in_sq == false) // toggle switch ' flag 💡
                in_sq = true; // ✅
            else
                in_sq = false; // ❌
            i++; // we skip the single quote.
            continue; // consume quote and evaluate from the start.
        }

        // 🟥 [2] - if we hit single quote " AND not in signle quote ': 
        if (str[i] == '"' && in_sq == false)
        {
            if (in_dq == false) // toggle switch " flag 💡
                in_dq = true; // ✅
            else
                in_dq = false; // ❌
            i++; // we skip the double quote.
            continue; // consume quote and evaluate from the start. avoid empty string case "" from substr.
        }
        // 🟦 [3] - 💲 we hit $ and NOT inside A single quote meaning expandable.
        if (str[i] == '$' && in_sq == false)
        {
            start = i++;
            while (ft_isalnum(str[i])) // inside a printable character
                i++;
            add_exp_token(&exp_tokens , ft_substr(str, start, i - start), in_sq, in_dq); // check if failed.

        }
        else
        {
            // 🟨  [4] - literal case: everything else.
            start = i++; // save start and move
            while (str[i]) // move as along as there is a string to read
            {
                // while in quote and in sq or in double move along ...
                if (str[i] == '$' && in_sq == false) // if we hit a $ we break, i is in that $ char
                    break;
                if (str[i] == '\'' || str[i] == '"') // same if quote, will be evaluated above
                    break;
                i++;
            }
            add_exp_token(&exp_tokens , ft_substr(str, start, i - start), in_sq, in_dq); // check for fail.
        }
    }
    return (exp_tokens); // NULL for now.
}
