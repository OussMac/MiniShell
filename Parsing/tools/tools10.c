#include "../minishell.h"

void    list_cleaner(t_token **list)
{
    t_token *temp;

    temp = NULL;
    while ((*list) != NULL)
    {
        free(temp);
        free((*list)->identity);
        temp = (*list);
        if ((*list)->next == NULL)
        {
            free(temp);
            break ;
        }
        (*list) = (*list)->next;
    }
}

static void clean_redlist(t_red **red)
{
    t_red *temp;

    temp = NULL;
    while ((*red) != NULL)
    {
        free(temp);
        free((*red)->value);
        temp = (*red);
        if ((*red)->next == NULL)
        {
            free(temp);
            break ;
        }
        (*red) = (*red)->next;
    }
}

void    cleaner_red(t_token *list)
{
    while (list != NULL)
    {
        if (list->red != NULL)
            clean_redlist(&list->red);
        list = list->next;
    }
}