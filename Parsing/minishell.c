#include "minishell.h"

void f()
{
    system("leaks minishell");
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_fd_leaks(void)
{
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "lsof -p %d", getpid());
    printf("=== FD Leak Check ===\n");
    system(cmd);
}


void voiders(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
}

int main(int argc, char **argv, char **env)
{
    // atexit(f);
    // atexit(check_fd_leaks);

    t_tree *tree;
    t_data data;
    t_brace_t br;
    t_token *token;
    t_token *prompts;

    char *input = NULL;
    voiders(argc, argv, env);
    init_data_struct(&data, env);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        // Pre parsing Braces case of (ls << eof)
        ft_bzero(&br, sizeof(t_brace_t));
        input = readline("\033[32mMaster@Mindv2.0> \033[0m");
        if (input == NULL)
            break ;
        if (input[0] != '\0')
            add_history(input);
        token = get_identity(input, &data, &br);
        prompts = re_identity(token);
        tree = build_tree(prompts);
        print_tree(tree);
        execute_tree(tree, &data, env, NULL);
    }
    free(input);
}

// ls || cat | (cat) && clear | (cat & pwd) case to check in tree

/*REMINIDER 
    heredoc delimiter if a next delimiter to be joined has quotes
    its not going to be saved, since we save for only the first one
    put in mind to fix later inchallah

    need to check for $ if its wrapped around quotes it will be the only
    token that we should not remove quotes from, KEEP IN MIND

    keep in mind to add the red pointer into the tree nodes.

    > Heredoc file descriptor transporation
    
    > Pre parsing for this case (ls << eof)

    > Expanding not removing quotes
    > re_built instead of tree in case of no command or operator
*/