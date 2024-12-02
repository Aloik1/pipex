NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror ##-g3 -fsanitize=address
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = $(LIBFT_DIR)/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRC = 		pipex_bonus.c 	utils_bonus.c \
		utils2_bonus.c \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(PRINTF):
	make -C $(PRINTF_DIR)
$(LIBFT):
	make -C $(LIBFT_DIR)
$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

clean:
	make clean -C $(PRINTF_DIR)
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re