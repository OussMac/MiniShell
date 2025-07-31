#include "../../minishell.h"

int edge_braces(char *input, t_data *data)
{
	if (!ft_strchr(input, ')')
		&& !ft_strchr(input, '('))
		return (1);
	
}