# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>

// Macros
# define F 1
# define S 0
# define T 1
# define N 0
# define OLDPWD 0
# define PWD 1
# define ANOMALY -1111
# define POINT_N_GET 0
# define POINT_ONLY 0

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
# define N_LINE "\n"

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

// Linked List Holding The Enviroment
typedef struct s_envlist
{
    char *variable;
    bool pointed;
    struct s_envlist *next;
}   t_envlist;

// Struct Holding MasterMind Data
typedef struct s_data
{
    int exit_status;
    int is_child;
    t_envlist *env;
}   t_data;

// Signal Tools
void    sig_handler(int signum);

// Debbugers
void    linkednev_db(t_envlist **env);
void    debbuger_tk(t_token *id_class);

// Initialization
void init_data_struct(t_data *data, char **env);

// Envirement List Tools
t_envlist   *add_variable(char *variable);
t_envlist   *get_last_node(t_envlist *env);
char        *ft_strjoin(char *s1, char *s2);
char        *cpy_variable(char *var_place, char *variable);
void         add_to_env(t_envlist **env, t_envlist *variable);

// Identity Tools
int     get_len(char *str);
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
char    *scrap(int *index, char *scrapped);
char    *scrap_string(char *input, int *index);
int     len_of_quote(char *input, char quote_case, int index);
char    *scrap_quote(char *input, int *index, int quote_case);

// Units of Tokening
void    first_unit(char *input, int *i, t_token *id, t_token **id_class);
void    sec_unit(char *input, int *index, t_token *id, t_token **id_class);
void    third_unit(char *input, int *index, t_token *id, t_token **id_class);
void    forth_unit(char *input, int *i, t_token *id, t_token **id_class);

// Builtins
void pwd(char **env);
void echo(char **argv);
void ft_env(t_envlist **env);
void ft_exit(char **argv, t_data *data);

// Tools Of Builtins
int     double_len(char **argv);
long    ft_atol(const char *str);
char    **double_dup(char **env);
char    *ft_strdup(const char *s1);
char    *get_variable(char *pointed);
int     ft_strcmp(char *s1, char *s2);
char    *ft_strtrim(char *s1, char *set);
int     ft_strncmp(char *s1, char *s2, int n);
char    *ft_substr(char *s, unsigned int start, size_t len);
char    *set_pointer(t_data *data, char *pointed, int len, int mode);