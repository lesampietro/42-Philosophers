# Variables
NAME= philosophers
CC= cc
CFLAGS= -Wall -Wextra -Werror
INCLUDES= -I philo/includes
BIN= ./bin/
SRC_D= ./philo/src/
SRC=	main.c \
		get_time.c \
		init_philo.c \
		monitor_routine.c \
		parse_input.c \
		philo_routine.c \
		utils.c

SRC:= $(addprefix $(SRC_D), $(SRC))
OBJS:= $(patsubst %.c, $(BIN)%.o, $(notdir $(SRC)))

# Rules
all: $(NAME)

$(BIN)%.o: $(SRC_D)%.c
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && echo "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@echo "Creating $(NAME)"
	$(CC) $(OBJS) $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
