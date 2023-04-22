SRC = philo_main.c philo_utils.c philo_utils2.c philo_thread.c \
		philo_norm_did_this_to_me.c

OBJ = $(SRC:.c=.o)

NAME = philo

CFLAGS = -Wall -Wextra -Werror

PNAME = philo

EXTRA = -lpthread #-fsanitize=thread -g 

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	gcc $(OBJ) $(CFLAGS) -o $(PNAME) $(EXTRA)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(PNAME)

re: fclean all