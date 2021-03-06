# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 18:45:34 by cjeon             #+#    #+#              #
#    Updated: 2022/02/24 20:37:04 by cjeon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror#-g -fsanitize=address -fsanitize=undefined

NAME = minirt
INCLUDE_ROOT = include
SRCS_ROOT = src
SRCS := \
	color.c ft_window.c light.c get_next_line.c get_next_line_utils.c \
	math_utils.c minirt.c object_cylinder.c object_plane.c object_sphere.c \
	object_utils.c objects.c parse_camera.c parse_cylinder.c parse_light.c \
	parse_plane.c parse_sphere.c parser.c parser_utils.c scene.c utils.c \
	vector3_complex.c vector3_scaler.c vector3_simple.c vector3_utils.c \
	scene_ray.c parse_general.c mlx_event.c
SRCS := $(addprefix $(SRCS_ROOT)/, $(SRCS))
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
INCLUDES := \
	color.h ft_window.h get_next_line.h light.h minirt.h \
	objects.h parser.h scene.h utils.h vector3.h mlx_event.h
INCLUDES := $(addprefix $(SRCS_ROOT)/, $(INCLUDES))

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

-include $(DEPS)

%.o : %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_ROOT) -MMD -c -o $@ $<

all : $(NAME)

clean :
	make -C $(MLX_ROOT) clean
	make -C $(LIBFT_ROOT) clean
	rm -f $(OBJS) $(DEPS)

fclean : clean
	make -C $(LIBFT_ROOT) fclean
	rm -f $(NAME)

re : fclean all

norm :
	@echo "[-] version"
	@norminette -v
	@echo "[-] check miniRT"
	@norminette $(SRCS)
	@norminette $(INCLUDES)
	@echo "[-] check libft"
	@$(MAKE) -C $(LIBFT_ROOT) norm

.PHONY : all clean fclean re norm