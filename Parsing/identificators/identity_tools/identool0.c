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
	new->br = 0;
	new->op = 0;
	new->firsts = 0;
	new->brace_o = 0;
	new->op_case = 0;
	new->brace_c = 0;
	new->end = false;
	new->space_next = 0;
	new->here_doc_fd = -1;
	new->space_next = false;
	new->was_single_quote = 0;
	new->was_double_quote = 0;
}

static void re_initialization(t_token *new, t_token *old)
{
	new->br = old->br;
	new->op = old->op;
	new->end = old->end;
	new->firsts = old->firsts;
	new->brace_c = old->brace_c;
	new->brace_o = old->brace_o;
	new->op_case = old->op_case;
	new->space_next = old->space_next;
	new->space_next = old->space_next;
	new->was_double_quote = old->was_double_quote;
	new->was_single_quote = old->was_single_quote;
	if (old->here_doc_fd != -1)
		new->here_doc_fd = dup(old->here_doc_fd);
}

void	add_back_identity(t_token **lst, t_token *new, int mode)
{
	if (!new || !lst)
		return ;
	if (!ft_strcmp(new->identity, "<<"))
	{
		new->here_done = 0;
		new->here_times = 1;
	}
	if (mode == INIT)
		init_properties(new);
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;	
}

t_token	*add_identity(char *content, enum grammar tok, int mode, t_token *infos)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		exit(F);
	if (new_node)
	{
		new_node->identity = ft_strdup(content);
		// cpy_identity(new_node->identity, content); why ??
		new_node->tok = tok;
		new_node->next = NULL;
	}
	if (mode == INIT)
		re_initialization(new_node, infos);
	return (new_node);
}

