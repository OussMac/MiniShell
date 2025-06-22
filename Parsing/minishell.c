#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    t_tree *tree;
    t_data data;
    t_brace_t br;
    t_token *token;
    t_token *prompts;

    char *input = NULL;
    init_data_struct(&data, env);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        ft_bzero(&br, sizeof(t_brace_t));
        input = readline("\033[32mMaster@Mindv1.1> \033[0m");
        if (input == NULL)
            break ;
        if (input[0] != '\0')
            add_history(input);
        token = get_identity(input, &data, &br);
        prompts = re_identity(token);
        build_tree(prompts);
        // debbuger_tk(token);
    }
    free(input);
}
