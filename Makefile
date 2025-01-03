NAME = cub3d

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

SRCS_DIR = ./srcs/

GNL_DIR = gnl/
VALIDATION_DIR = $(SRCS_DIR)validation/
UTILS_DIR = $(SRCS_DIR)utils/
RAYCASTING_DIR = $(SRCS_DIR)raycasting/

INCLUDES_DIR = ./includes/

SRCS = \
		$(GNL_DIR)get_next_line.c \
		$(GNL_DIR)get_next_line_utils.c \
		$(SRCS_DIR)main.c \
		$(VALIDATION_DIR)texture_validation.c \
		$(VALIDATION_DIR)map_validation.c \
		$(VALIDATION_DIR)data_validation.c \
		$(VALIDATION_DIR)validation_utils_1.c \
		$(VALIDATION_DIR)validation_utils_2.c \
		$(RAYCASTING_DIR)raycasting_utils_1.c \
		$(RAYCASTING_DIR)raycasting_utils_2.c \
		$(RAYCASTING_DIR)raycast.c \
		$(RAYCASTING_DIR)movement.c \
		$(RAYCASTING_DIR)minimap.c \
		$(RAYCASTING_DIR)minimap_utils.c \

OBJS = $(SRCS:.c=.o)

# DEBUG = -fsanitize=address -g
# MacOS
CFLAGS =  -Wall -Werror -Wextra -Imlx
# Linux
# CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
# MacOS
MLXFLAGS = -Lmlx -lmlx -framework OpenGl -framework Appkit -lm
# Linux
# MLXFLAGS = -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

CC = cc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)
	make -C $(LIBFT_DIR) bonus

%.o: %.c Makefile $(INCLUDES_DIR)cub3d.h $(INCLUDES_DIR)get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
