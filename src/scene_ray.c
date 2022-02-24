/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:33:11 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 14:24:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

/*
** if camera direction is y+ then vup is z-
** or camera direction is y- then vup is z+
** otherwise vup is y+
*/
t_vector3	get_vup(t_vector3 dir)
{
	const static t_vector3	vup[3] = {
		{0, 0, -1},
		{0, 0, 1},
		{0, 1, 0}
	};
	const static t_vector3	y_dir[2] = {
		{0, 1, 0},
		{0, -1, 0}
	};

	if (v3_equal(dir, y_dir[0]))
		return (vup[0]);
	else if (v3_equal(dir, y_dir[1]))
		return (vup[1]);
	else
		return (vup[2]);
}

t_vector3	get_local_ray_dir(const t_scene *scene, double y, double x)
{
	t_vector3				dir;
	double					width;
	double					height;
	const static t_range	window_range[2] = {
		{RANGE_CLOSED, 0, WINDOW_WIDTH - 1},
		{RANGE_CLOSED, 0, WINDOW_HEIGHT - 1}
	};

	width = tan(scene->camera.fov_w / 2) * FOCAL_LEN;
	height = tan(scene->camera.fov_h / 2) * FOCAL_LEN;
	dir.x = scaler_rescale(x + 0.5, window_range[0], \
				get_range(RANGE_CLOSED, -width, width));
	dir.y = scaler_rescale(y + 0.5, window_range[1], \
				get_range(RANGE_CLOSED, height, -height));
	dir.z = 1;
	return (dir);
}

t_transform_matrix	get_transform_matrix(const t_scene *scene, t_vector3 *xs, \
											t_vector3 *ys)
{
	static double	m[4][3];

	m[0][0] = xs->x;
	m[0][1] = xs->y;
	m[0][2] = xs->z;
	m[1][0] = ys->x;
	m[1][1] = ys->y;
	m[1][2] = ys->z;
	m[2][0] = scene->camera.dir.x;
	m[2][1] = scene->camera.dir.y;
	m[2][2] = scene->camera.dir.z;
	m[3][0] = scene->camera.origin.x;
	m[3][1] = scene->camera.origin.y;
	m[3][2] = scene->camera.origin.z;
	return (m);
}

t_vector3	get_global_ray_dir(const t_scene *scene, t_vector3 local)
{
	t_vector3			vup;
	t_vector3			xs;
	t_vector3			ys;
	t_transform_matrix	m;

	vup = get_vup(scene->camera.dir);
	xs = v3_cross(vup, scene->camera.dir);
	ys = v3_cross(scene->camera.dir, xs);
	m = get_transform_matrix(scene, &xs, &ys);
	return (v3_to_unit(v3_transform(local, m)));
}

t_ray	get_rotated_ray(const t_scene *scene, double y, double x)
{
	t_vector3	local;
	t_ray		ray;

	local = get_local_ray_dir(scene, y, x);
	ray.dir = get_global_ray_dir(scene, local);
	ray.origin = scene->camera.origin;
	return (ray);
}
