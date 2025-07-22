CC = cc 
SANITIZE=# -fsanitize=address -g
CFLAG = -I$(READLINE_DIR)/include # zdt readline library (MAC) -Wall -Wextra -Werror
READLINE_DIR := ../lib/readline/install
LDFLAGS += -L$(READLINE_DIR)/lib -lreadline -lhistory -lncurses
H = minishell.h 
NAME = minishell
SRC = minishell.c Identificators/identity_tools/identool0.c\
		Identificators/identify.c Identificators/identity_tools/identool1.c \
		tools/tool.c\
		tools/tool2.c Identificators/units.c \
		Debbugers/Tokens_db.c Debbugers/Linkedenv.c \
		Builtins/echo.c Builtins/env.c Builtins/pwd.c \
		Signal_handlers/sig_handlers.c\
		Builtins/exit.c Builtins/export.c \
		tools/tools3.c tools/tools4.c tools/tools5.c\
		Builtins/Builtins_t/B_tools.c Builtins/Builtins_t/B_tools2.c\
		Builtins/Builtins_t/B_tools3.c tools/tools6.c \
		Builtins/Builtins_t/B_tools4.c tools/tools7.c \
		Builtins/Builtins_t/B_tools5.c\
		Syntax/syntax.c Syntax/syntax2.c Syntax/syntax3.c\
		Identificators/identity_tools/identool2.c\
		Identificators/identity_tools/identool3.c\
		Identificators/identity_tools/identool4.c\
		tools/tools8.c Identificators/identity_tools/identool5.c\
		Identificators/identity_tools/identool6.c\
		tools/tools9.c Identificators/identity_tools/identool7.c\
		Identificators/identity_tools/identool8.c\
		Re_Identificators/re_identity.c Re_Identificators/re_identity_tools/re_identool0.c\
		Re_Identificators/re_identity_tools/re_identool1.c\
		Re_Identificators/re_identity_tools/re_identool2.c\
		Re_Identificators/re_identity_tools/re_identool3.c\
		Re_Identificators/re_identity_tools/re_identool4.c\
		Re_Identificators/re_identity_tools/re_identool5.c\
		MasterMind/system_mind0.c MasterMind/system_mind1.c\
		MasterMind/Mind_tools/mind_tools0.c MasterMind/Mind_tools/mind_tools1.c\
		MasterMind/Mind_tools/mind_tools2.c MasterMind/Mind_tools/mind_tools3.c \
		Debbugers/dbg_tree.c tools/tools10.c\
		\
		\
		\
		../Execute/tree_executers/execute_tree.c ../Execute/tree_executers/merge_utils.c \
		../Execute/tree_pipeline/tree_pipeline.c ../Execute/tree_executers/free_tree.c \
		../Execute/tree_executers/shortcircuit.c ../Execute/tree_executers/handle_red.c \
		../Execute/o_builtins/o_bultins.c ../Execute/o_builtins/o_echo.c \
		../Execute/o_builtins/o_cd.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAG) $(SANITIZE) $(LDFLAGS) -lreadline -o $(NAME)

%.o: %.c $(H)
	@$(CC) $(CFLAG) $(SANITIZE) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     
