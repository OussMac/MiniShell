#include "../minishell.h"

void debbuger_tk(t_token *id_class)
{
    t_token *trav = id_class;
    while (trav != NULL)
    {
        printf("identity> %s\n", trav->identity);
        if (trav->tok == 0)
            printf("ID-> PIPE\n");
        else if (trav->tok == 1)
            printf("ID-> RED_IN_ID\n");
        else if (trav->tok == 2)
            printf("ID-> RED_OUT_ID\n");
        else if (trav->tok == 3)
            printf("ID-> RED_APP_ID\n");
        else if (trav->tok == 4)
            printf("ID-> HERE_DOC_ID\n");
        else if (trav->tok == 5)
            printf("ID-> AND_ID\n");
        else if (trav->tok == 6)
            printf("ID-> OR_ID\n");
        else if (trav->tok == 7)
            printf("ID-> BRACE_O_ID\n");
        else if (trav->tok == 8)
            printf("ID-> BRACE_C_ID\n");
        else if (trav->tok == 9)
            printf("ID-> WILD_CARD_ID\n");
        else if (trav->tok == 10)
            printf("ID-> EXPANSION_ID\n");
        else if (trav->tok == 11)
            printf("ID-> S_QUOTE_ID\n");
        else if (trav->tok == 12)
            printf("ID-> D_QUOTE_ID\n");
        else if (trav->tok == 15)
            printf("ID-> SPACE_ID\n");
        else if (trav->tok == 13)
            printf("ID-> STRING_ID\n");
        else if (trav->tok == 14)
            printf("ID-> DEL_ID\n");
        trav = trav->next;
        printf("****************\n");
    }
}