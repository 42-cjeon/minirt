/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/08 10:58:44 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

#include "minirt.h"
#include "mlx.h"
#include "utils.h"
#include "ft_window.h"
#include "scene.h"
#include "parser.h"

void print_vector3(t_vector3 v)
{
	printf("[x:%.3lf y:%.3lf z:%.3lf ]\n", v.x, v.y, v.z);
}

void print_color3(t_color3 c)
{
	printf("[R:%.2lf G:%.2lf B:%.2lf]\n", c.x, c.y, c.z);
}

void print_sphere(t_sphere *sp)
{
	printf("OBJ-SPHERE\n");
	printf("  -origin : "); print_vector3(sp->origin);
	printf("  -radius : %lf\n", sp->radius);
	printf("  -albedo : "); print_vector3(sp->phong.albedo);
}

void print_point_light(t_point_light *pl)
{
	printf("LIG-POINT\n");
	printf("  -origin : "); print_vector3(pl->origin);
	printf("  -ratio  : %lf\n", pl->ratio);
	printf("  -color  : "); print_color3(pl->color);
}

void print_objects(t_list *node)
{
	while (node)
	{
		if (node->type == OBJ_SPHERE)
			print_sphere(node->content);
		node = node->next;
	}
}

void print_lights(t_list *node)
{
	while (node)
	{
		if (node->type == LIG_POINT)
			print_point_light(node->content);
		node = node->next;
	}
}

void print_scene(t_scene *scene)
{
	printf("Ambient\n");
	printf("  -ratio : [%lf]\n", scene->gl.ratio);
	printf("  -color : "); print_color3(scene->gl.ambient);
	printf("Camera\n");
	printf("  -origin : "); print_vector3(scene->camera.origin);
	printf("  -dir    : "); print_vector3(scene->camera.dir);
	printf("  -fov    : [%lfrad]\n", scene->camera.fov_w);
	print_objects(scene->obj_list);
	print_lights(scene->light_list);
}

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
		print_scene(&scene);
	else
		return (RT_ERR_FILE);
	if (get_minirt_window(&window))
		return (RT_ERR_MLX);
	if (draw_scene(&scene))
		return (RT_ERR_SYSCALL);
	return (RT_SUCCESS);
}