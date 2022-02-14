/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/14 17:46:29 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include "minirt.h"
#include "mlx.h"
#include "utils.h"
#include "ft_window.h"
#include "scene.h"
#include "parser.h"
#include "objects.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_window	window;
	t_scene		scene;

	if (argc != 2)
	{
		ft_puterror("usage: ./minirt filename.rt");
		return (RT_ERR_ARG);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_perror("miniRT");
		return (RT_ERR_FILE);
	}
	if (!parse_scene(fd, &scene))
	{
		t_cylinder *cy;
		cy = malloc(sizeof(t_cylinder));
		cy->diameter = 0.1;
		cy->height = 10;
		cy->origin = (t_vector3){0, -0.5, 1};
		cy->dir = (t_vector3){0, 0, 1};
		cy->phong = (t_phong){{1,1,1}};
		ft_lstadd_front(&scene.obj_list, ft_lstnew(OBJ_CYLINDER, cy));
		print_scene(&scene);
	}
	else
		return (RT_ERR_FILE);
	if (get_minirt_window(&window))
		return (RT_ERR_MLX);
	if (draw_scene(&window, &scene))
		return (RT_ERR_SYSCALL);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, window.image.img_ptr, 0, 0);
	mlx_loop(window.mlx_ptr);
	return (RT_SUCCESS);
}