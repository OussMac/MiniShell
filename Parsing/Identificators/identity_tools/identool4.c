#include "../../minishell.h"

static char *name_generator(void)
{
    long n;
    long *nb;
    char *name;
    char *gename;

    nb = malloc(sizeof(long *));
    if (!nb)
        return (NULL);
    n = (long)nb;
    name = ft_itoa(n);
    if (!name)
        return (free(nb), NULL);
    gename = ft_strjoin("/tmp/", name);
    if (!gename)
        return(free(name), free(nb), NULL);
    free(name);
    free(nb);
    return (gename);
}

static void cpy_to_file(char *in, t_data *data)
{
    int i;

    i = 0;
    while (in[i])
    {
        write(data->here_fd, &in[i], 1);
        i++;
    }
    write(data->here_fd, "\n", 1);
    free(in);
}

static char *scrap_del(char *delimiter)
{
    int i;
    char *del;

    i = 0;
    del = malloc(get_len(delimiter) + 1);
    if (!del)
        return (NULL);
    while(delimiter[i])
    {
        del[i] = delimiter[i];
        i++;
    }
    del[i] = '\0';
    return (del);
}

static int  open_heredoc(t_token *id_class, t_token *curr, t_data *data, t_brace_t *br)
{
    char *in;
    char *del;
    char *gename;

    if (!sef_doc(id_class, data, br))
        return (0);
    gename = name_generator();
    del = scrap_del(get_delimiter(curr));
    data->here_fd = open(gename, O_CREAT | O_WRONLY, 0777);
    if (data->here_fd == -1)
        return (0);
    unlink(gename);
    // int fd = dup(STDOUT_FILENO);
    in = readline("Here_doc> ");
    while (ft_strcmp(del, in))
    {
        if (!in)
        {
            puterror("MasterMind: Here-Doc Delimited By End Of File\n");
            close(data->here_fd);
            break;
        }
        cpy_to_file(in, data);
        in = readline("Here_doc> ");
    }
    store_fd(id_class, data);
    // dup2(fd, STDOUT_FILENO);
    return(free(del), free(in), free(gename), 1);
}

int here_doc_check(t_token *id_class, t_data *data, t_brace_t *br)
{
    t_token *curr;

    curr = id_class;
    while (curr != NULL)
    {
        if (requirements(curr, id_class, data))
        {
            id_class->here_times = 0; // ?? set it on the same first node??
            if (!change_id(curr->next, data)
                || !open_heredoc(id_class, curr, data, br))
                return (0);
        }
        curr = curr->next;
    }
    return (1);
}
