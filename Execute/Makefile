CC = cc 
CFLAG = -Wall -Wextra -Werror
HEADER = execute.h 
NAME = execute
SRC = main.c parse_helpers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo " _, _  _,  _, ___ __, __,   _, _ _ _, _ __,"
	@echo " |\/| /_\ (_   |  |_  |_)   |\/| | |\ | | \\"
	@echo " |  | | | , )  |  |   | \   |  | | | \| |_/"
	@echo " ~  ~ ~ ~  ~   ~  ~~~ ~ ~   ~  ~ ~ ~  ~ ~  "
	@$(CC) $(OBJ) $(CFLAG) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAG) -c $< -o $@

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all     