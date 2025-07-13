#include "../execute.h"

int o_echo(t_cmd *node, t_osdata *osdata)
{
    int i = 1;
    int newline = 1;

    // Step 1: Handle multiple -n options
    while (node->argv[i] && ft_strncmp(node->argv[i], "-n", 2) == 0)
    {
        int j = 2;
        while (node->argv[i][j] == 'n')
            j++;

        if (node->argv[i][j] != '\0') // not like -nnn
            break;

        newline = 0;
        i++;
    }

    // Step 2: Print the rest of the arguments
    while (node->argv[i])
    {
        printf(YLW"%s", node->argv[i]);
        if (node->argv[i + 1])
            printf(" ");
        i++;
    }

    // Step 3: Newline if not suppressed
    if (newline)
        printf("\n");
    printf(RST);
    fflush(stdout); // fllush buffer in case of no newline

    return (EXIT_SUCCESS);
}
