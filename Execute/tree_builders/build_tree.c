#include "../execute.h"

// ---------------------------  simple tree builder  ---------------------------------

static char **g_tokv; // the token vector (double array) i get from tokenization.
static int    g_pos; // the current index position we are reading from in the array.




static char *last_strdup(char *str)
{
    char *ptr;
    int i = 0;
    int last_space = -1;

    while (str[i])
    {
        if (str[i] == ' ')
            last_space = i;
        i++;
    }

    if (last_space == -1)
        last_space = i; // No spaces found, take the whole string

    ptr = malloc(i - last_space);
    if (!ptr)
        return (perror("malloc"), NULL);

    int j = 0;
    while (last_space < i)
    {
        ptr[j++] = str[++last_space];
    }
    ptr[j] = '\0';
    return (ptr);
}



static char *uspace_strdup(char *str)
{
    char *ptr;

    int i = 0;

    while (str[i])
    {
        if(str[i] == ' ' || str[i] == '\0')
            break;
        i++;
    }
    
    ptr = malloc (i + 1);
    if (!ptr)
        return (perror ("malloc"),NULL);
    int j = 0;
    while (j < i)
    {
        ptr[j++] = str[i++];
    }
    ptr[j] = '\0';
    return (ptr);
}


// split and take the first arg
static char *trimmer_br(char *str)
{
    char **trimmed;

    if (strchr(str,  '('))
    {
        
        trimmed = ft_split(str, '(');
        return (uspace_strdup(str + 1));
    }
    else if (strchr(str,  ')'))
    {
        trimmed = ft_split(str, ')');
        return (last_strdup(str)); // last word allocated string minus the bracket essentially like substr but in one function for this purpose
    }
    else
        return (ft_strdup(str));
    return (NULL);
}



static t_cmd *brace_trim(t_cmd *node)
{
    char *temp;
    int i, j;

    i = 0;
    while (node->argv[i])
    {
        temp = node->argv[i]; //ptr to old string
        node->argv[i] = trimmer_br(node->argv[i]); // new allocated str
        printf("trimmed =>> %s\n", node->argv[i]);
        free(temp); // free old one
        i++;
    }
    return (node);
}

static char *peek(void) 
{
    return (g_tokv[g_pos]);
}

static char *consume(void) {
    return (g_tokv[g_pos++]);
}

static bool match(char *str) 
{
    if (g_tokv[g_pos] && !ft_strcmp(g_tokv[g_pos], str)) 
    {
        g_pos++;
        return (true);
    }
    return (false);
}

static char *join_range(int start, int end) {
    int i;
    int len = 0;

    i = start;
    while (i < end)
    {
        len += ft_strlen(g_tokv[i]) + 1; // +1 for space or null terminator.
        i++;
    }

    char *res = malloc(len);
    if (!res)
    {
        perror("join range malloc: ");
        return (NULL);
    }

    res[0] = '\0';
    i = start;
    while (i < end)
    {
        ft_strcat(res, g_tokv[i]);
        if (i + 1 < end)
            ft_strcat(res, " ");
        i++;
    }

    return (res);
}

static t_cmd *parse_and_or(t_osdata *osdata);
static t_cmd *parse_pipeline(t_osdata *osdata);
static t_cmd *parse_redirect(t_osdata *osdata);
static t_cmd *parse_simple(t_osdata *osdata);

static t_cmd *parse_simple(t_osdata *osdata) 
{
    if (match("(")) 
    {
        t_cmd *sub = parse_and_or(osdata);

        if (!match(")")) 
        {
            perror("ouss_parser: expected ')'");
            return (NULL);
        }

        t_cmd *node = malloc(sizeof *node);
        if (!node) 
        { 
            perror("GROUP malloc"); 
            return (NULL); 
        }
        node->id    = O_GROUP;
        node->argv  = NULL;
        node->left  = sub;
        node->right = NULL;
        return (node);
    }

    int start = g_pos;

    while (g_tokv[g_pos] && ft_strcmp(peek(), "|")
       && ft_strcmp(peek(), "&&") && ft_strcmp(peek(), "||")
       && ft_strcmp(peek(), "<") && ft_strcmp(peek(), ">")
       && ft_strcmp(peek(), "<<") && ft_strcmp(peek(), ">>")
       && ft_strcmp(peek(), ")"))
    {
        g_pos++;
    }
    if (g_pos == start) 
    {
        perror("ouss_parser: expected command");
        return (NULL);
    }

    char *joined = join_range(start, g_pos);
    if (!joined) 
    {
        perror("joined malloc: ");
        return (NULL);
    }

    t_cmd *leaf = create_leaf(joined, O_CMD, osdata);
    free(joined);
    return (leaf);
}

static t_cmd *parse_redirect(t_osdata *osdata) {
    t_cmd *node = parse_simple(osdata);
    if (!node) return NULL;
    while (peek()
       && (!ft_strcmp(peek(), "<")
        || !ft_strcmp(peek(), ">")
        || !ft_strcmp(peek(), "<<")
        || !ft_strcmp(peek(), ">>")))
    {
        char *op = consume();
        t_cmd *file = parse_simple(osdata);
        if (!file) return NULL;
        t_cmd *redir = malloc(sizeof *redir);
        if (!redir) { perror("malloc"); return NULL; }
        redir->id    = O_REDIR;
        redir->left  = node;
        redir->right = file;
        node = redir;
    }
    return node;
}

static t_cmd *parse_pipeline(t_osdata *osdata) {
    t_cmd *node = parse_redirect(osdata);
    if (!node) return NULL;
    while (match("|")) {
        t_cmd *rhs = parse_redirect(osdata);
        if (!rhs) return NULL;
        t_cmd *pipe = malloc(sizeof *pipe);
        if (!pipe) { perror("malloc"); return NULL; }
        pipe->id    = O_PIPE;
        pipe->left  = node;
        pipe->right = rhs;
        node = pipe;
    }
    return node;
}

static t_cmd *parse_and_or(t_osdata *osdata) {
    t_cmd *node = parse_pipeline(osdata);
    if (!node) return NULL;
    while (1) {
        if (match("&&")) {
            t_cmd *rhs = parse_pipeline(osdata);
            if (!rhs) return NULL;
            t_cmd *andn = malloc(sizeof *andn);
            if (!andn) { perror("malloc"); return NULL; }
            andn->id    = O_AND;
            andn->left  = node;
            andn->right = rhs;
            node = andn;
        }
        else if (match("||")) {
            t_cmd *rhs = parse_pipeline(osdata);
            if (!rhs) return NULL;
            t_cmd *orn = malloc(sizeof *orn);
            if (!orn) { perror("malloc"); return NULL; }
            orn->id    = O_OR;
            orn->left  = node;
            orn->right = rhs;
            node = orn;
        }
        else
            break;
    }
    return node;
}

t_cmd *build_tree(t_osdata *osdata, char **tokens) 
{
    g_tokv = tokens;
    g_pos  = 0;
    t_cmd *root = parse_and_or(osdata);
    if (peek()) {
        fprintf(stderr, "ouss_parser: unexpected token '%s'\n", peek());
        return NULL;
    }
    return root;
}
