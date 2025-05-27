CC = cc 
CFLAG = #
H = minishell.h 
NAME = minishell
SRC = minishell.c Identificators/identity_tools/identool0.c\
		Identificators/identify.c Identificators/identity_tools/identool1.c tools/tool.c\
		tools/tool2.c Identificators/units.c \
		Debbugers/Tokens_db.c Debbugers/Linkedenv.c Builtins/echo.c Builtins/env.c Builtins/pwd.c Signal_handlers/sig_handlers.c\
		Builtins/exit.c Builtins/export.c tools/tools3.c tools/tools4.c tools/tools5.c\
		Builtins/Builtins_t/B_tools.c Builtins/Builtins_t/B_tools2.c\
		Builtins/Builtins_t/B_tools3.c tools/tools6.c \
		Builtins/Builtins_t/B_tools4.c tools/tools7.c \
		Builtins/Builtins_t/B_tools5.c\
		\
		Syntax/syntax.c Syntax/syntax2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAG) -lreadline -o $(NAME)

%.o: %.c $(H)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     