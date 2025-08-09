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

t_tree *masterpasrse(char *input, t_data *data, t_token **prompts)
{
    t_token *token;

    token = get_identity(input, data);
    *prompts = re_identity(token);
    return (build_tree(*prompts));
}

int main(int argc, char **argv, char **env)
{
    atexit(f);
    // atexit(check_fd_leaks);
    char *input;
    t_data data;
    t_tree *tree;
    t_token *re_built;

    tree = NULL;
    input = NULL;
    voiders(argc, argv, env);
    init_data_struct(&data, env);
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        input = readline("\033[32mMaster@Mindv3.0> \033[0m");
        if (input == NULL)
            break ;
        if (input[0] != '\0')
            add_history(input);
        tree = masterpasrse(input, &data, &re_built);
        execute_tree(tree, &data, env, re_built);
    }
    free_argv(data.env_vec);
    free_envlist(data.env);
    return (free(input), EXIT_SUCCESS);
}

// ls || cat | (cat) && clear | (cat & pwd) case to check in tree
// Master@Mindv3.0> echo foo | grep "found" > log && ls < input || echo "found" > success [ Case Solved ]

/* Parsing Reminder

    heredoc delimiter if a next delimiter to be joined has quotes
    its not going to be saved, since we save for only the first one
    put in mind to fix later inchallah (CHECKED)

    need to check for $ if its wrapped around quotes it will be the only
    token that we should not remove quotes from, KEEP IN MIND (CHECKED)

    keep in mind to add the red pointer into the tree nodes. (CHECKED)

    > Heredoc file descriptor transporation (Checked)
    
    > Pre parsing for this case (ls << eof) (Checked)

    > Delimiter trimming with no WhiteSpaces (Checked)

    > Add the Command itself to the first arg in arg struct (Checked)

    > Check the red_system need to protect Malloc Failure (Checked)

    > Need to add the Arg Struct and Red struct into the cleaning (Checked)

    > Ft_strdup Failure in building the tree recursively (TODO) NEED TO CHECK CAREFULLY HOW IT SHOULD BE PROTECTED

    > re_built instead of tree in case of no command or operator (CHECKED)

    Change in Plan, the plan in which i leave quotes for expanding, i wont leave them, it interrupt
    the normal flow of removing quotes [ Case awk '{print $1}'], the quotes should be removed before
    given to execve in the Execution

*/

/*
    Execution Reminder 
    Master@Mindv3.0> ./minishell
    Migrane: command not found: ./minishell
    Need to handle ./Executable

    Case --> if multiple heredoc found redirected inisde of a command, close the firsts ones, 
    and only execute the command on the last heredoc
    Case --> [ls < l | cat] if the redirection failed nothing will be piped
*/