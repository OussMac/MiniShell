#include "../execute.h"

/*
 * a list of your separators, longest first.
 * You can tweak or add more as needed.
 */
static const char *seps[] = {
    "||", "&&", "<<", ">>",
    "|",  "<",  ">", "(", ")", 
    NULL
};

/*
 * return the length of the matching separator at s[i], or 0 if none.
 */
size_t match_sep(const char *s)
{
	int	i = 0;
	while (seps[i])
	{
		int len = ft_strlen(seps[i]);
		if (!ft_strncmp(s, seps[i], len))
            return len;
		i++;
	}
    return 0;
}

/*
 * split `s` into tokens: words (runs of non‑space, non‑sep chars)
 * and separators (from seps array). Returns a NULL‑terminated array.
 */
char **better_split(const char *s)
{
    size_t  cap = 8, count = 0;
    char  **tokens = malloc(cap * sizeof(char *));
    size_t  i = 0;

    if (!tokens)
        return NULL;

    while (s[i])
    {
        /* 1) skip any spaces */
        while (s[i] && (s[i] == ' ' || s[i] == '\t'))
            i++;

        if (!s[i])
            break;

        /* 2) check for a separator match */
        size_t slen = match_sep(s + i);
        if (slen)
        {
            if (count + 1 >= cap)
            {
                cap *= 2;
                tokens = realloc(tokens, cap * sizeof(char *));
            }
            tokens[count++] = ft_substr(s, i, slen);
            i += slen;
        }
        else
        {
            /* 3) otherwise, grab a word */
            size_t start = i;
            while (s[i]
                && s[i] != ' '
                && s[i] != '\t'
                && match_sep(s + i) == 0)
                i++;

            if (count + 1 >= cap)
            {
                cap *= 2;
                tokens = realloc(tokens, cap * sizeof(char *));
            }
            tokens[count++] = ft_substr(s, start, i - start);
        }
    }

    /* NULL‑terminate */
    tokens[count] = NULL;
    return tokens;
}
