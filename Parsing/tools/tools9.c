#include "../minishell.h"

int list_size(t_token *list)
{
    int size;

    size = 0;
    while (list)
    {
        size++;
        list = list->next;
    }
    return(size);
}