# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>


// Macros
# define F 1
# define S 0

# define T 1
# define N 0

// Operators
# define OR '|'
# define AND '&'
# define PIPE '|'
# define RED_IN '<'
# define RED_OUT '>'
# define RED_APP '>'
# define HERE_DOC '<'
# define WILD_CARD '*'
# define EXPANSION '$'
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define SPACE ' '
# define BRACE_OP '('
# define BRACE_CL ')'

// Enum Of IDs
enum grammar
{
    PIPE_ID, // |
    RED_IN_ID, // <
    RED_OUT_ID, // >
    RED_APP_ID, // >>
    HERE_DOC_ID, // <<
    STRING_ID,
    FILE_ID,
    ARG_ID, // -ARG
    AND_ID, // &&
    OR_ID, // ||
    WILD_CARD_ID, // *
    EXPANSION_ID, // $
    S_QUOTE_ID, // ''
    D_QUOTE_ID, // ""
    SPACE_ID,
    BRACE_O_ID, // (
    BRACE_C_ID, // )
};

// Linked List To Store Each Entity
// Each Entity With His Id
typedef struct s_token
{
    char *identity;
    int concat;
    enum grammar tok;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
    int exit_status;
    char **o_env;
}   t_data;

// Flags To Manage The Order Of Scraping
typedef struct s_flg
{
    int cmd;
    int pipe;
    int red_in;
    int red_out;
    int red_app;
    int here_doc;
    int and_op;
    int or_op;
    int argg;
    int expansion;
    int wildcard;
    int once;
    int sync_s;
    int sync_sc;
    int quote;
    int sync_quote;
} t_flg;

//Identity Tools
int     get_len(char *str);
void    sig_handler(int signum);
void debbuger_tk(t_token *id_class);
t_token	*ft_lstlast(t_token *lst);
void    ft_bzero(void *s, size_t n);
int     check_doubles(char x, char x2);
void    cpy_identity(char *dst, char *src);
void    get_identity(char *input);
int      check_alpha(char x, char x2);
void	add_back_identity(t_token **lst, t_token *new);
t_token	*add_identity(char *content, enum grammar tok);
int     len_of_string(char *input, int index);
int     ft_strnstr(char *haystack, char *needle, size_t len);
void    identity_scraping(char *ident, enum grammar en, t_token *id, t_token **id_class);

// Identity Scrapers
char *scrap(int *index, char *scrapped);
char *scrap_string(char *input, int *index);
int len_of_quote(char *input, char quote_case, int index);
char *scrap_quote(char *input, int *index, int quote_case);

// Units of Tokening
void    first_unit(char *input, int *i, t_token *id, t_token **id_class);
void    sec_unit(char *input, int *index, t_token *id, t_token **id_class);
void    third_unit(char *input, int *index, t_token *id, t_token **id_class);
void    forth_unit(char *input, int *i, t_token *id, t_token **id_class);

// Builtins
void pwd(char **env);
void echo(char **argv);
void ft_env(int unset, char **env);

// Tools Of Builtins
int     ft_strcmp(char *s1, char *s2);