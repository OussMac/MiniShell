#include "../execute.h"

// these functions are called from pocket_insertion.

size_t	o_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char    *normal_text(char *str, int *i)
{
    int start;

    start = *i;
	while (str[*i] && str[*i] != '$')
			(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *standalone(int *i)
{
    (*i)++;
    return (ft_strdup("$"));
}

int  expand_key_wrapper(char **pockets, char *str, t_data *data)
{
    data->pc.value = expand_key(str, data, data->pc.keylen, &data->pc.i);
    if (data->pc.value != NULL)
        pockets[data->pc.j++] = data->pc.value;
    else
        pockets[data->pc.j++] = ft_strdup(""); // non printable to detect not passing it to execve.
    return(EXIT_SUCCESS);
}