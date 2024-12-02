NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror ##-g3 -fsanitize=address
BONUS_DIR = bonus
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF_DIR = $(LIBFT_DIR)/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
SRC = 		pipex.c 			utils.c \
		utils2.c \

SRC_BONUS = 	$(BONUS_DIR)/pipex_bonus.c 	$(BONUS_DIR)/utils_bonus.c \
		$(BONUS_DIR)/utils2_bonus.c \

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(PRINTF):
	make -C $(PRINTF_DIR)
$(LIBFT):
	make -C $(LIBFT_DIR)
$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

bonus: $(LIBFT) $(PRINTF) $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_BONUS) 


clean:
	make clean -C $(PRINTF_DIR)
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)
re: fclean all

.PHONY: all clean fclean re