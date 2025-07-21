#include "../execute.h"

static int  red_wrraper(t_tree *node, t_data *data, t_grammar red_id)
{
    return (EXIT_SUCCESS);
}

static int red_in(t_red *red, t_data *data)
{
    int in_fd;

    in_fd = open(red->value, O_RDONLY);
    if (in_fd == -1)
        return (dprintf(2 , "Migrane: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(in_fd, STDIN_FILENO) == -1)
        return (dprintf(2 , "Migrane: %s", red->value), perror(" "), close(in_fd), EXIT_FAILURE);
    close(in_fd);
    return (EXIT_SUCCESS);
}

static int red_out(t_red *red, t_data *data)
{
    return (EXIT_SUCCESS);
}

static int  red_append(t_red *red, t_data *data)
{
    return (EXIT_SUCCESS);
}

int handle_red(t_tree *node, t_data *data)
{
    t_red   *curr_red;

    curr_red = node->red;
    while (curr_red)
    {
        if (curr_red->tok == INPUT_FILE_ID)
        {
            int saved_in;
            saved_in = dup(STDIN_FILENO);
            if (red_in(curr_red, data) != EXIT_SUCCESS)
                return (EXIT_FAILURE);
            exec_node(node, data);
            dup2(saved_in, STDIN_FILENO);
            close(saved_in);
        }
        else if (curr_red->tok == OUTPUT_FILE_ID)
        {
            if (red_out(curr_red, data) != EXIT_SUCCESS)
                return (EXIT_FAILURE);
        }
        else if (curr_red->tok == INPUT_APP_FILE_ID)
        {
            if (red_append(curr_red, data) != EXIT_SUCCESS)
                return (EXIT_FAILURE);
        }
        curr_red = curr_red->next;
    }
    return (EXIT_SUCCESS);
}
