#include "../execute.h"

// might need outside.
void    free_arg_list(t_arg *arg)
{
    t_arg   *tmp;

    if (!arg)
        return ;
    while (arg)
    {

        tmp = arg->next;
        free(arg->value);
        free(arg);
        arg = tmp;
    }
}

static size_t   arglist_size(t_arg *arg)
{
    size_t  size;

    size = 0;
    while (arg)
    {
        size++;
        arg = arg->next;
    }
    return (size);
}

// entry function
char **convert_list_to_argv(t_arg *arg, t_data *data)
{
    char        **argv;
    size_t      argc;
    int         i;
    t_arg       *free_head;

    free_head = arg;
    argc = arglist_size(arg);
    argv = malloc ((argc + 1)* sizeof(char *));
    if (!argv)
        return (free_arg_list(free_head), NULL); // cleanup return;
    if (expand_list(arg, data) != EXIT_SUCCESS) // expanding.
        return (free_arg_list(free_head), free(argv), NULL);
    i = 0;
    while(arg)
    {
        argv[i] = join_system(&arg);  // join args if needed.
        if (!argv[i])
        {
            while (i-- > 0) // cleanup
                free(argv[i]);
            return (free(argv), free_arg_list(free_head), NULL);
        }
        i++;
    }
    return (argv[i] = NULL, free_arg_list(free_head), argv);
}
