#include "../minishell.h"

void ft_env(t_envlist **env)
{
    t_envlist *trav;

    trav = *env;
    while(trav != NULL)
    {
        printf("%s", trav->variable);
        trav = trav->next;
    }
}