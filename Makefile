# Variables
NAME= philo
CC= cc
CFLAGS= -Wall -Wextra -Werror -pthread -g3
INCLUDES= -I philo/includes
BIN= ./bin/
SRC_D= ./philo/src/
SRC=	main.c \
		parse_input.c \
		init_philos.c \
		get_time.c \
		philo_routine.c \
		monitor_routine.c \
		cleaning_routine.c \
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
	$(CC) $(OBJS) $(INCLUDES) $(CFLAGS) -o $(NAME)

clean:
	rm -rf $(BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
