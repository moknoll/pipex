CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../libft
LDFLAGS = -L../libft -lft
SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
