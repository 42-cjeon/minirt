CC = cc
CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined #-Werror

NAME = minirt
INCLUDE_ROOT = include
SRCS_ROOT = src
SRCS := \
	camera.c color.c ft_window.c \
	get_next_line.c get_next_line_utils.c light.c minirt.c \
	objects.c parser.c scene.c utils.c vector3.c
SRCS := $(addprefix $(SRCS_ROOT)/, $(SRCS))
OBJS = $(SRCS:.c=.o)

LIBFT_ROOT = $(SRCS_ROOT)/libft
LIBFT = $(LIBFT_ROOT)/libft.a

MLX_ROOT = $(SRCS_ROOT)/minilibx
MLX = $(MLX_ROOT)/libmlx.a
MLX_FRAMEWORK = -framework OpenGL -framework AppKit

$(NAME) : $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(MLX_FRAMEWORK) -lz -I$(INCLUDE_ROOT) -o $@ $^

$(LIBFT) :
	make -C $(LIBFT_ROOT) all

$(MLX) :
	make -C $(MLX_ROOT) all

%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_ROOT) -c -o $@ $<

all : $(NAME)

clean :
	make -C $(MLX_ROOT) clean
	make -C $(LIBFT_ROOT) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(LIBFT_ROOT) fclean
	rm -f $(NAME)

re : fclean all

norm :
	norminette -v
	@echo "[-] check miniRT srcs"
	norminette $(SRCS)
	@echo "[-] check libft srcs"

.PHONY : all clean fclean re norm