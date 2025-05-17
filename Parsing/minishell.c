#include "minishell.h"

static void voiders(int argc, char **argv)
{
    (void)argc;
    (void)argv;
}

int main(int argc, char **argv, char **env)
{
    // char *input = NULL;
    t_data data;

    voiders(argc, argv);
    init_data_struct(&data, env);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    // while(1)
    // {
    //     input = readline("\033[32mMaster@Mindv1.0> \033[0m");
    //     if (input == NULL)
    //         break;
    //     if (input[0] != '\0')
    //         add_history(input);
    //     get_identity(input);
    // }
    // free(input);
}