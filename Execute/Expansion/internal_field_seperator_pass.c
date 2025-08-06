#include "../execute.h"

static size_t ifs_list_size(t_ifs *curr)
{
    size_t size;

    size = 0;
    while (curr)
    {
        size++;
        curr = curr->next;
    }
    return (size);
}

static void free_ifs_list(t_ifs *ifs)
{
    t_ifs   *tmp;

    if (!ifs)
        return ;
    while (ifs)
    {
        tmp = ifs->next;
        free(ifs->string);
        free(ifs);
        ifs = tmp;
    }
}

static int  add_ifs_back(t_ifs **head, char *str)
{
    t_ifs   *new;
    t_ifs   *curr;

    new = malloc (sizeof(t_ifs));
    if (!new)
        return (EXIT_FAILURE);
    new->string = ft_strdup(str);
    if (!new->string)
        return (free(new), EXIT_FAILURE);
    new->next = NULL;
    if (!*head)
        *head = new;
    else
    {
        curr = *head;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
    return (EXIT_SUCCESS);
}

static char **ifs_list_to_argv(t_ifs *head)
{
    size_t  size;
    t_ifs   *curr;
    char    **argv;
    size_t  i;

    i = 0;
    size = ifs_list_size(head);
    argv = malloc(sizeof(char *) * (size + 1));
    if (!argv)
        return (NULL);
    curr = head;
    while (i < size)
    {
        argv[i] = ft_strdup(curr->string);
        if (!argv[i])
        {
            while (--i >= 0)
                free(argv[i]);
            return (free(argv), NULL);
        }
        curr = curr->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

// // takes the argv but is joined i want to resplit but only the parts that have the delims i put
char    **IFS_pass(char **argv)
{
    char    **ifs_split;
    char    **new_argv;
    t_ifs   *ifs_list;
    int     i;
    int     j;

    i = 0;
    ifs_list = NULL;
    while (argv[i])
    {
        if (has_delim(argv[i]))
        {
            ifs_split = ft_split(argv[i], (char)27);
            if (!ifs_split)
                return (NULL);
            j = 0;
            while (ifs_split[j])
            {
                if (add_ifs_back(&ifs_list, ifs_split[j]) != EXIT_SUCCESS)
                    return (free_ifs_list(ifs_list), free_argv(ifs_split), NULL);
                j++;
            }
            free_argv(ifs_split);
        }
        else
        {
            if (add_ifs_back(&ifs_list, argv[i]) != EXIT_SUCCESS)
                return (free_ifs_list(ifs_list), NULL);
        }
       i++;
    }
    new_argv = ifs_list_to_argv(ifs_list);
    if (!new_argv)
        return (free_ifs_list(ifs_list), NULL);
    free_ifs_list(ifs_list);
    return (new_argv);
}
