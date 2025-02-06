# Variables
NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES= -I includes
BIN= ./bin/
SRC_D= ./src/
SRC =	main.c \
		parse_input.c \
		utils.c

SRC:= $(addprefix $(SRC_D), $(SRC))
OBJS:= $(patsubst $(SRC_D)%.c, $(BIN)%.o, $(SRC))

# Rules
all: $(NAME)

$(BIN)%.o: $(SRC_D)%.c
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) -g3 -o $@ -c $< && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@echo "Creating $(NAME)"
	$(CC) $(OBJS) $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
