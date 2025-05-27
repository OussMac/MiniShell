#include "../../minishell.h"

void linkednexp_db(t_exportlist **env)
{
    t_exportlist *trav;

    trav = *env;
    printf("Debbugging The Linked EXP...\n");
    while(trav != NULL)
    {
        printf("%s%s\n", trav->variable, trav->value);
        trav = trav->next;
    }
}

t_exportlist *get_last_exp(t_exportlist *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void add_to_exp(t_exportlist **env, t_exportlist *variable)
{
	if (*env)
		get_last_exp(*env)->next = variable;
	else
		*env = variable;
}

t_exportlist *add_exp_value(char *env_var, char *value)
{
	t_exportlist *node;
    char *var;
    char *d_quote;
    char *declare_var;

	node = malloc(sizeof(t_exportlist));
    declare_var = ft_strdup("declare -x ");
    var = ft_strjoin(declare_var, env_var);
    node->variable = var;
    value = add_slash(value);
    d_quote = ft_strjoin("=\"", value);
    node->value = ft_strjoin(d_quote, "\"");
	// cpy_variable(node->variable, variable); why ??
	node->next = NULL;
	return (node);
}

void    list_exp(t_exportlist **exp, char **env)
{
    int i;
    char **exp_var;
    char *exp_value_case;
    char *exp_value_base;
    t_exportlist *node;

    i = 0;
    while(env[i])
    {
        if (!ft_strnstr(env[i], "LS_COLORS=", 10))
        {
            exp_var = ft_split(env[i], '=');
            node = add_exp_value(exp_var[0], exp_var[1]);
            add_to_exp(exp, node);
        }
        else if (ft_strnstr(env[i], "LS_COLORS=", 10))
        {
            // rememeber this one needs to be modified, if someone created a folder in which = exists
            // it will be splited in the env also in exp
            // CHANGE IT AFTER
            // u can change it in the export workspace to test and verify the new approach
            exp_value_case = ft_strtrim(env[i], "LS_COLORS");
            exp_value_base = copy_var(exp_value_case);
            node = add_exp_value("LS_COLORS", exp_value_base);
            add_to_exp(exp, node);
        }
        i++;   
    }
}