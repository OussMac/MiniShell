#include "../execute.h"

static bool ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c >= 'a' && c <= 'z')
		return (true);
	return (false);
}

// expands exit status && pid.
static char *expand_special_cases(char *str, t_data *data, int *i)
{
    if (str[*i + 1] == '?')
    {
	    *i += 2; // move $ ? ==> +2 
        return (o_ft_itoa(data->exit_status));
    }
    else if (str[*i + 1] == '$')
    {
        *i += 2; // move $ $ ==> +2 
        return (o_ft_itoa(data->pid));
    }
    return (NULL); // fallback should never happen.
}

static void init_pocket_struct(t_pocket *pc)
{
    pc->i = 0;
    pc->j = 0;
    pc->keylen = 0;
    pc->value = NULL;
}

// entry function
int	pocket_insertion(char **pockets, char *str, t_data *data)
{
    init_pocket_struct(&data->pc);
	while (str[data->pc.i])
	{
		if (str[data->pc.i] == '$')
		{
			if (str[data->pc.i + 1] == '?' || str[data->pc.i + 1] == '$')
				pockets[data->pc.j++] = expand_special_cases(str, data, &data->pc.i);
			else 
			{
                data->pc.keylen = 0;
				while (ft_isalnum(str[data->pc.i + 1 + data->pc.keylen]) || str[data->pc.i + 1 + data->pc.keylen] == '_')
					data->pc.keylen++;
				if (data->pc.keylen > 0) // valid key
					expand_key_wrapper(pockets, str, data); // check for fail.
				else // standalone $
					pockets[data->pc.j++] = standalone(&data->pc.i);
			}
		}
		else
			pockets[data->pc.j++] = normal_text(str, &data->pc.i);
	}
	return (pockets[data->pc.j] = NULL, EXIT_SUCCESS);
}
