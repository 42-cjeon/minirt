/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:01:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/10 17:58:35 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"
#include "scene.h"
#include "ray.h"
#include "color.h"
#include "objects.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t	get_pixel_color(t_scene *scene, t_ray ray, double y, double x)
{
	t_hit_record	record;
	t_color3		color_vec;

	record.distence = INFINITY;
	if (hit_object(ray, scene->obj_list, &record))
		color_vec = calc_color(scene, &record);
	else
		color_vec = v3_lerp((t_vector3){0.5, 0.7, 1.0}, (t_vector3){1, 1, 1}, y / WINDOW_HEIGHT);
	return (v3_to_color(color_vec));
}
#include <stdio.h>
#include <stdlib.h>

t_ray	get_rotated_ray(const t_scene *scene, double y, double x)
{
	const t_vector3	vup = {0, 1, 0};
	t_vector3		u;
	t_vector3		v;
	t_qt qt;
	t_qt	ray;
	t_ray r;

	y = (scene->camera.fov_h / 2) - (scene->camera.fov_h * ((y + 0.5) / WINDOW_HEIGHT));
	x = (scene->camera.fov_w * ((x + 0.5) / WINDOW_WIDTH)) - (scene->camera.fov_w / 2);
	/*
	(scene->camera.fov_h / 2) - (scene->camera.fov_h * (y / WINDOW_HEIGHT))


	(scene->camera.fov_w * (x / WINDOW_WIDTH)) - (scene->camera.fov_w / 2)
	*/
	//y = M_PI / 2;
	//x = M_PI / 2;
	u = v3_cross(vup, scene->camera.ray.dir);
	v = v3_cross(scene->camera.ray.dir, u);
	qt.re = cos(y / 2);
	qt.im = v3_mul_scaler(u, sin(y / 2));
	ray.re = 0;
	ray.im = scene->camera.ray.dir;
	ray = qt_mul(qt, ray);
	qt.im = v3_mul_scaler(u, -sin(y / 2));
	ray = qt_mul(ray, qt);

	qt.re = cos(x / 2);
	qt.im = v3_mul_scaler(v, sin(x / 2));
	ray.re = 0;
	ray.im = scene->camera.ray.dir;
	ray = qt_mul(qt, ray);
	qt.im = v3_mul_scaler(v, -sin(x / 2));
	ray = qt_mul(ray, qt);

	r.origin = scene->camera.ray.origin;
	r.dir = ray.im;
	return (r);
	//printf("ORGINAL :"); print_vector3(scene->camera.ray.dir);
	//printf("Axis    :"); print_vector3(u);
	//printf("ANGLE   : 90deg\n");
	//printf("ROTATED :"); print_vector3(ray.im);
	//exit(1);
	//return (ray.im);
}

int	draw_scene(t_window *window, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;
	uint32_t	*img;

	img = window->image.data;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while(j < WINDOW_WIDTH)
		{
			ray = get_rotated_ray(scene, i, j);
			//ray = scene->camera.ray;
			*img = get_pixel_color(scene, ray, i, j);
			//exit(10);
			img++;
			j++;
		}
		i++;
	}
	return (0);
}