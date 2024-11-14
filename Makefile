NAME = philo

SRC = src/main.c src/philosophers.c src/checker.c src/mutex_utils.c src/ft_utils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = clang
all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lpthread

%.o : %.c
	$(CC) $(FLAGS) -I/src/ -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
