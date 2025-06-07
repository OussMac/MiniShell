# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>

// Macros
# define NL 0
# define C 2
# define F 1
# define S 0
# define T 1
# define N 0
# define SYN 1
# define PWD 1
# define ENV 0
# define EXP 1
# define OLDPWD 0
# define UNIT_HEREDOC 0
# define UNIT_SPACE_NEXT 1
# define HEREDOC1 1
# define HEREDOC2 2
# define ONE_QUOTE 9
# define DUO_QUOTE 10
# define POINT_ONLY 0
# define POINT_N_GET 0
# define ANOMALY -1111
# define SYNTAX "MasterMind: Syntax Error Near "
# define CL_BEFORE "MasterMind: Closing Brace With No Open"
# define BRACE_ERR "MasterMind: Invalid Use Of Braces"
# define QUOTES_ERR "MasterMind: Invalid Use Of Quotes"

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
# define TAB '\t'

// Enum Of IDs
enum grammar
{
    PIPE_ID, // |
    RED_IN_ID, // <
    RED_OUT_ID, // >
    RED_APP_ID, // >>
    HERE_DOC_ID, // <<
    AND_ID, // &&
    OR_ID, // ||
    BRACE_O_ID, // (
    BRACE_C_ID, // )
    S_QUOTE_ID, // ''
    D_QUOTE_ID, // ""
    STRING_ID, // Commands & Arguments
    DEL_ID, // Here_doc Delimiter
};

// Linked List To Store Each Entity
// Each Entity With His Id
typedef struct s_token
{
    int op;
    int br;
    int brace_c;
    int brace_o;
    int firsts;
    int op_case;
    int here_times;
    int here_done;
    bool space_next;
    int was_single_quote;
    int was_double_quote;
    char *identity;
    enum grammar tok;
    struct s_token *next;
}   t_token;

// Linked List Holding The Enviroment
typedef struct s_envlist
{
    char *value;
    bool pointed;
    char *variable;
    struct s_envlist *next;
}   t_envlist;

// Linked List Holding The ExportList
typedef struct s_exportlist
{
    char *value;
    char *variable;
    bool pointed;
    struct s_exportlist *next;
}   t_exportlist;

// Struct Holding MasterMind Data
typedef struct s_data
{
    int to_exp;
    int to_env;
    int append;
    int is_child;
    int here_fd;
    int here_case;
    int exit_status;
    t_exportlist *exp;
    t_envlist *env;
}   t_data;

typedef struct s_brace_t
{
    int brace_op;
    int brace_cl;
    int quote_state;
}   t_brace_t;

// Signal Tools
void    sig_handler(int signum);

// Debbugers
void    linkednev_db(t_envlist **env);
void    debbuger_tk(t_token *id_class);

// Initialization
void init_data_struct(t_data *data, char **env);

// Environment List Tools
char        *copy_var(char *value_case);
t_envlist   *get_last_node(t_envlist *env);
char        *ft_strjoin(char *s1, char *s2);
char        **ft_split(char const *s, char c);
char        *cpy_variable(char *var_place, char *variable);
void         add_to_env(t_envlist **env, t_envlist *variable);
t_envlist   *add_variable_value(char *variable, char *value);

// Identity Tools
int         get_len(char *str);
void        puterror(char *str);
int         all_whitespaces(char x);
t_token	    *ft_lstlast(t_token *lst);
void        ft_bzero(void *s, size_t n);
int         check_doubles(char x, char x2);
void        cpy_identity(char *dst, char *src);
t_token     *get_identity(char *input, t_data *data);
int         check_alpha(char x, char x2);
void	    add_back_identity(t_token **lst, t_token *new);
t_token	    *add_identity(char *content, enum grammar tok);
int         len_of_string(char *input, int index);
int         ft_strnstr(char *haystack, char *needle, size_t len);
int         unit_call_here_doc(t_token **id_class, char *input, t_data *data);
void        unit_call_space_next(t_token *id_class, char *input, int *index);
int         identity_scraping(char *ident, enum grammar en, t_token *id, t_token **id_class);

// Identity Scrapers
char    *scrap(int *index, char *scrapped);
char    *scrap_string(char *input, int *index);
int     len_of_quote(char *input, char quote_case, int index);
char    *scrap_quote(char *input, int *index, int quote_case);
char    *scrap_braces(char *input, int *index, char *brace);

// Units of Tokening
void    first_unit(char *input, int *i, t_token *id, t_token **id_class);
void    sec_unit(char *input, int *index, t_token *id, t_token **id_class);
void    third_unit(char *input, int *index, t_token *id, t_token **id_class);
int     forth_unit(char *input, int *i, t_token *id, t_token **id_class);

// Builtins
void    pwd(char **env);
void    echo(char **argv);
void    ft_env(t_envlist **env);
void    ft_exit(char **argv, t_data *data);
void    unset(char **args, t_data *data);
void    ft_cd(char *path, t_data *data);
void    export(t_data *data, char **args, int len);

// Tools Of Builtins
int     double_len(char **argv);
long    ft_atol(const char *str);
char    **double_dup(char **env);
char    *ft_strdup(const char *s1);
char    *get_variable(char *pointed);
int     ft_strcmp(char *s1, char *s2);
int     ft_strchr(const char *s, int c);
char    *ft_strtrim(char *s1, char *set);
int     ft_strncmp(char *s1, char *s2, int n);
char    *ft_substr(char *s, unsigned int start, size_t len);
char    *set_pointer(t_data *data, char *pointed, int len, int mode);

// Export List tools
int             to_append(char *arg);
char            *scrap_var(char *arg);
char            *add_slash(char *value);
char            *scrap_value(char *arg);
void            scan_ops(t_exportlist **exp);
int             valide_string(char *arg);
t_exportlist    *get_last_exp(t_exportlist *env);
void            linkednexp_db(t_exportlist **env);
void            save_var(char *arg, t_data *data);
int             set_flags(char *arg, t_data *data);
int             valide_exp(char *arg, t_data *data);
void            list_exp(t_exportlist **exp, char **env);
void            append(t_data *data, char *arg, int mode);
int             replace(char *arg, t_data *data, int mode);
t_exportlist    *add_exp_value(char *env_var, char *value);
void            change_value(t_data *data, char *arg, int mode);
int             change_append(char *arg, t_data *data, int mode);
void            add_to_exp(t_exportlist **env, t_exportlist *variable);
char            *set_pointer_exp(t_data *data, char *pointed, int len, int mode);

// Syntax Verification
void    puterror(char *str);
int     realt_braces(char *input, t_brace_t *br);
int     syntax_verify(t_token *token, t_data *data);
int     doubles_verify(t_token *token, t_data *data);
void    print_error(char *error, char *err, int mode);
void    syntax_error_found(t_token *curr, t_data *data);
int     realt_quotes(char *input, int doubles_case, int index, char *err);

// Here_Document Tools
char    *ft_itoa(int n);
int     list_size(t_token *list);
void    takeoff_quotes(t_token *tok);
void    space_flag(t_token *id_class);
char    *get_delimiter(t_token *token);
int     get_here_times(t_token *id_class);
int     change_id(t_token *next_heredoc, t_data *data);
int     here_doc_check(t_token *id_class, t_data *data);
int     delimiter_next(t_token *next_heredoc, t_data *data);
int     requirements(t_token *curr, t_token *id_class, t_data *data);


// test to be removed after
int printer(t_token *curr);