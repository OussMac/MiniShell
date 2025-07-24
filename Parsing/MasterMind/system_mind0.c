#include "../minishell.h"

t_tree *build_tree(t_token *id_class)
{
    t_tree *tree;
    t_token *yard;

    tree = NULL;
    yard = NULL;
    if (id_class == NULL)
        return (NULL);
    yard = shunting_yard_algorithm(id_class);
    if (!yard)
    {
        cleaner_red(id_class);
        list_cleaner(&id_class);
    }
    list_cleaner(&id_class);
    recursive_build(yard, &tree);
    list_cleaner(&yard);
    return (tree);
}

static void init_tree(t_tree **node)
{
    *node = malloc(sizeof(t_tree));
    if (!*node)
        exit(F);
    (*node)->value = NULL;
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->red = NULL;
    (*node)->argv = NULL;
    (*node)->was_s_quote = 0;
    (*node)->was_d_quote = 0;
    (*node)->op_case = 0;
}

static t_token *last_unchecked(t_token *yard)
{
    t_token *curr;

    curr = yard;
    while (curr != NULL)
    {
        if (curr->next && curr->next->marked)
            return (curr);
        curr = curr->next;
    }
    return (ft_lstlast(yard));
}

static void put_token(t_tree *tree, t_token *token)
{
    tree->value = ft_strdup(token->identity);
    // Malloc Failure
    tree->tok = token->tok;
    tree->op_case = token->op_case;
    tree->red = token->red;
    tree->was_s_quote = token->was_single_quote;
    tree->was_d_quote = token->was_double_quote;
    token->marked = true;
}

void    recursive_build(t_token *yard, t_tree **tree)
{
    t_token *token;

    init_tree(tree);
    token = last_unchecked(yard);
    put_token(*tree, token);
    if (token->op_case)
    {
        recursive_build(yard, &(*tree)->right);
        recursive_build(yard, &(*tree)->left);
    }
    else
        return ;
}
