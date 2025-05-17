CC = cc 
CFLAG = -Wall -Wextra -Werror
H = minishell.h 
NAME = minishell
SRC = minishell.c identificators/identity_tools/identool0.c\
		identificators/identify.c identificators/identity_tools/identool1.c tools/tool.c\
		tools/tool2.c identificators/units.c \
		Debbugers/Tokens_db.c  Debbugers/Linkedenv.c Builtins/echo.c Builtins/env.c Builtins/pwd.c Signal_handlers/sig_handlers.c\
		Builtins/exit.c tools/tools3.c tools/tools4.c tools/tools5.c

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