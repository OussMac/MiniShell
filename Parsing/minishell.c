#include "minishell.h"

static void voiders(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
}

int main(int argc, char **argv, char **env)
{
    t_flg flg;
    char *input = NULL;
    
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    voiders(argc, argv, env);
    while(1)
    {
        ft_bzero(&flg, sizeof(flg));
        input = readline("\033[32mMaster@Mindv1.0> \033[0m");
        if (input == NULL)
            break;
        if (input[0] != '\0')
            add_history(input);
        get_identity(input);
    }
    free(input);
}