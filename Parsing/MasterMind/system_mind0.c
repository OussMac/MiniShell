#include "../minishell.h"

void build_tree(t_token *id_class)
{
    t_token *yard;

    yard = shunting_yard_algorithm(id_class);
}
