#include "../minishell.h"

void identity_scraping(char *ident, enum grammar en,
        t_token *id, t_token **id_class)
{
    id = add_identity(ident, en);
    add_back_identity(id_class, id);
}

void get_identity(char *input)
{
    int i;
    t_token *id;
    t_token *id_class;

    i = 0;
    id = NULL;
    id_class = NULL; // why seggev??
    while (input[i])
    {
        first_unit(input, &i, id, &id_class);
        sec_unit(input, &i, id, &id_class);
        third_unit(input, &i, id, &id_class);
        forth_unit(input, &i, id, &id_class);
        i++;
    }
    debbuger_tk(id_class);
}
