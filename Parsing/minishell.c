#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    t_data data;
    char *input = NULL;
    t_token *token;

    init_data_struct(&data, env);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        input = readline("\033[32mMaster@Mindv1.0> \033[0m");
        if (input == NULL)
            break;
        if (input[0] != '\0')
            add_history(input);
        token = get_identity(input);
        syntax_verify(token, &data);
        // debbuger_tk(token);
    }
    free(input);
}
