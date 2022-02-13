/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:01:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/13 16:17:31 by cjeon            ###   ########.fr       */
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

int v3_equal(t_vector3 u, t_vector3 v)
{
	return (
		u.x == v.x
		&& u.y == v.y
		&& u.z == v.z
	);
}

t_ray	get_rotated_ray(const t_scene *scene, double y, double x)
{
	t_vector3	vup;
	t_vector3	local;

	t_ray		ray;
	t_vector3	xs;
	t_vector3	ys;
	t_vector3	zs;
	t_vector3	os;

	if (v3_equal(scene->camera.ray.dir, (t_vector3){0, 1, 0}))
		vup = (t_vector3){0, 0, -1};
	else if (v3_equal(scene->camera.ray.dir, (t_vector3){0, -1, 0}))
		vup = (t_vector3){0, 0, 1};
	else
		vup = (t_vector3){0, 1, 0};	
	//y = (scene->camera.fov_h * ((y + 0.5) / WINDOW_HEIGHT)) - (scene->camera.fov_h / 2);
	//x = (scene->camera.fov_w * ((x + 0.5) / WINDOW_WIDTH)) - (scene->camera.fov_w / 2);
	double width = tan(scene->camera.fov_w / 2);
	double height = tan(scene->camera.fov_h / 2);
	
	local.y = scaler_rescale(y+0.5, (t_range){1, 0, WINDOW_HEIGHT - 1}, (t_range){1, height, -height});
	local.x = scaler_rescale(x+0.5, (t_range){1, 0, WINDOW_WIDTH - 1}, (t_range){1, -width, width});
	local.z = 1;

	xs = v3_cross(vup, scene->camera.ray.dir);
	ys = v3_cross(scene->camera.ray.dir, xs);
	zs = scene->camera.ray.dir;
	os = scene->camera.ray.origin;
	const double m[4][4] = {
		{xs.x,xs.y,xs.z,0},
		{ys.x,ys.y,ys.z,0},
		{zs.x,zs.y,zs.z,0},
		{os.x,os.y,os.z,1}
	};
	ray.dir.x = local.x * m[0][0] + local.y * m[1][0] + local.z * m[2][0] + m[3][0];
	ray.dir.y = local.x * m[0][1] + local.y * m[1][1] + local.z * m[2][1] + m[3][1];
	ray.dir.z = local.x * m[0][2] + local.y * m[1][2] + local.z * m[2][2] + m[3][2];
	ray.dir = v3_to_unit(ray.dir);
	ray.origin = os;

	return (ray);
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