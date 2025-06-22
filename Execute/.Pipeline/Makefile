CC = cc 
CFLAG = -Wall -Wextra -Werror
HEADER = pipex.h 
NAME = pipex
SRC = mult_pipe.c parse_helpers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Pipex Built."
	@$(CC) $(OBJ) $(CFLAG) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     