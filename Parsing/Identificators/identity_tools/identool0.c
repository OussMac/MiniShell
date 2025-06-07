#include "../../minishell.h"

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void init_properties(t_token *new)
{
	new->space_next = false;
	new->br = 0;
	new->brace_c = 0;
	new->brace_o = 0;
	new->firsts = 0;
	new->op = 0;
	new->op_case = 0;
	new->space_next = 0;
	new->was_double_quote = 0;
	new->was_single_quote = 0;
}

void	add_back_identity(t_token **lst, t_token *new)
{
	if (!new || !lst)
		return ;
	if (!ft_strcmp(new->identity, "<<"))
	{
		new->here_done = 0;
		new->here_times = 1;
	}
	init_properties(new);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;	
}

t_token	*add_identity(char *content, enum grammar tok)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		exit(F);
	if (new_node)
	{
		new_node->identity = content;
		// cpy_identity(new_node->identity, content); why ??
		new_node->tok = tok;
		new_node->next = NULL;
	}
	return (new_node);
}

