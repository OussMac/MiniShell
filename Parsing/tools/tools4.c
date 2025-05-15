#include "../minishell.h"

t_envlist *get_last_node(t_envlist *env)
{
	if (!env)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

t_envlist *add_variable(char *variable)
{
	t_envlist *node;

	node = malloc(sizeof(t_envlist));
	cpy_variable()
	node->next = NULL;
	return (node);
}

void *add_to_env(t_envlist **env, t_envlist *variable)
{
	if (!*env || !variable)
		return ;
	if (!*env)
		get_last_node(*env)->next = variable;
	else
		*env = variable;
}

char    *cpy_variable(char *var_place, char *variable)
{
    int i;

    i = 0;
    var_place = malloc(get_len(variable) + 1);
    while (variable[i])
    {
        var_place[i] = variable[i];
        i++;
    }
    var_place[i] = '\0';
    return (var_place);
}