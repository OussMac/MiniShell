#include "../execute.h"

static bool expandable_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (true);
        i++;
    }
    return (false);
}

static bool has_ifs(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (char)27)
            return (true);
        i++;
    }
    return (false);
}

static int red_in(t_red *red, t_data *data)
{
    int in_fd;

    in_fd = open(red->value, O_RDONLY);
    if (in_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(in_fd, STDIN_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(in_fd), EXIT_FAILURE);
    close(in_fd);
    return (EXIT_SUCCESS);
}

static int red_out(t_red *red, t_data *data)
{
    int out_fd;

    out_fd = open(red->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(out_fd, STDOUT_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(out_fd), EXIT_FAILURE);
    close(out_fd);
    return (EXIT_SUCCESS);
}

static int  red_append(t_red *red, t_data *data)
{
    int out_fd;

    out_fd = open(red->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (out_fd == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), EXIT_FAILURE);
    if (dup2(out_fd, STDOUT_FILENO) == -1)
        return (dprintf(2 , "Master@Mind: %s", red->value), perror(" "), close(out_fd), EXIT_FAILURE);
    close(out_fd);
    return (EXIT_SUCCESS);
}

static bool check_expanded_malloc(char **expanded, int *rs, t_data *data, char *curr_red_value)
{
    *expanded = expand_var(curr_red_value, data);
     if (!*expanded)
    {
            *rs = 0;
            return(EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static void init_red(t_data *data, int *rs)
{
    data->saved_in = dup(STDIN_FILENO);
    data->saved_out = dup(STDOUT_FILENO);
    *rs = 1;
}

int handle_red(t_tree *node, t_data *data)
{
    t_red   *curr_red = node->red;
    char    *expanded;
    bool    ambig;
    int redirection_success;

    init_red(data, &redirection_success);
    while (curr_red)
    {
        ambig = expandable_check(curr_red->value);
        if (check_expanded_malloc(&expanded, &redirection_success, data, curr_red->value) != EXIT_SUCCESS)
            break ;
        free(curr_red->value);
        curr_red->value = expanded;
        if ((has_ifs(curr_red->value) && ambig) || (curr_red->value[0] == (char)127 && curr_red->value[1] == '\0'))
        {
            redirection_success = 0;
            dprintf(2 , RED"Master@Mind: %s: ambiguous redirect"RST"\n", curr_red->value);
            break ;
        }
        if (curr_red->tok == INPUT_FILE_ID)
        {
            if (red_in(curr_red, data) != EXIT_SUCCESS)
            {
                redirection_success = 0;
                break;
            }
        }
        else if (curr_red->tok == OUTPUT_FILE_ID)
        {
            if (red_out(curr_red, data) != EXIT_SUCCESS)
            {
                redirection_success = 0;
                break;
            }
        }
        else if (curr_red->tok == INPUT_APP_FILE_ID)
        {
            if (red_append(curr_red, data) != EXIT_SUCCESS)
            {
                redirection_success = 0;
                break;
            }
        }
        curr_red = curr_red->next;
    }
    int status = EXIT_FAILURE;
    if (redirection_success)
        status = EXIT_SUCCESS;
    return (status);
}

void    restore_IO(int saved_in, int saved_out)
{
    // Always restore STDIN/STDOUT
    dup2(saved_in, STDIN_FILENO);
    dup2(saved_out, STDOUT_FILENO);
    close(saved_in);
    close(saved_out);
}
