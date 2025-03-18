CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../libft
LDFLAGS = -L../libft -lft
MAKEFLAGS += --silent
SRC = pipex.c pipex_utils.c pipex_utils2.c
OBJ = $(SRC:.c=.o)
NAME = pipex

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# Standard Ziel
all: libft $(NAME)

# Regel um libft zu bauen
libft:
	@echo "$(BLUE)Building libft...$(RESET)"
	@$(MAKE) -C ../libft

# Regel um pipex zu bauen
$(NAME): $(OBJ)
	@echo "$(YELLOW)Building: [#.........]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [##........]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [###.......]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [####......]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [######....]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [#######...]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [########..]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [#########.]$(RESET)\r"
	@sleep 0.2
	@echo "$(YELLOW)Building: [##########]$(RESET)\r\n"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN) ✅ pipex Build Complete! $(RESET)"

# Regel um .o Dateien zu erstellen
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Aufräumen
clean:
	rm -f $(OBJ)
	@$(MAKE) -C ../libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C ../libft fclean

re: fclean all

.PHONY: all clean fclean re libft
