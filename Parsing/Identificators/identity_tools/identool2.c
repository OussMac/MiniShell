#include "../../minishell.h"

char *scrap_braces(char *input, int *index, char *brace)
{
    int len;
    char *braces;

    len = get_len(brace);
    while (len--)
        (*index)++;
    // (*index)++; // REMEMEBER (*index--); bug ?
    return (ft_strdup(brace));
}
