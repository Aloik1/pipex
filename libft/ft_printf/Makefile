NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I.. -I.
LIBFT_DIR = ..
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ft_printf.c printf_x_big.c printf_c.c printf_d_i.c printf_s.c printf_u.c printf_x.c printf_p.c
OBJS = $(SRCS:.c=.o)
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


