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
    return (size);
}

int here_doc_ops(t_token *id_class, t_data *data, char *del)
{
    char *in;
    // int fd = dup(STDOUT_FILENO);
    in = readline("Here_doc> ");
    while (ft_strcmp(del, in))
    {
        if (!in)
        {
            puterror("MasterMind: Here-Doc Delimited By End Of File\n");
            close(data->here_fd);
            break;
            // may check for fd and laeks
        }
        cpy_to_file(in, data);
        in = readline("Here_doc> ");
    }
    if (!store_fd(id_class, data))
        return (free(in), 0);
    return (free(in), 1);
}