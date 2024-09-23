NAME = cub3d

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

GNL_DIR = gnl/

SRCS_DIR = ./srcs/

INCLUDES_DIR = ./includes/

SRCS = \
		$(GNL_DIR)get_next_line.c \
		$(GNL_DIR)get_next_line_utils.c \
		$(SRCS_DIR)main.c \
		$(SRCS_DIR)texture_validation.c \
		$(SRCS_DIR)map_validation.c \
		$(SRCS_DIR)utils.c \

OBJS = $(SRCS:.c=.o)

# DEBUG = -fsanitize=address -g
CFLAGS =  -Wall -Werror -Wextra -Imlx
# MLXFLAGS = -Lmlx -lmlx -framework OpenGl -framework Appkit -lm

CC = cc

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus
	$(CC) $(DEBUG) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

%.o: %.c Makefile $(INCLUDES_DIR)cub3d.h $(INCLUDES_DIR)get_next_line.h
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
