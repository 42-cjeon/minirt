/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:33:11 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 16:58:47 by cjeon            ###   ########.fr       */
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

t_vector3	get_local_ray_dir(t_scene *scene, double y, double x)
{
	t_vector3	dir;
	double		width;
	double		height;
	double		fov_h;

	width = tan(scene->camera.fov_w / 2) * scene->camera.focal_len;
	fov_h = scene->camera.fov_w * WINDOW_HEIGHT / WINDOW_WIDTH;
	height = tan(fov_h / 2) * scene->camera.focal_len;
	dir.x = scaler_rescale(x + 0.5, \
				get_range(RANGE_CLOSED, 0, WINDOW_WIDTH - 1), \
				get_range(RANGE_CLOSED, -width, width));
	dir.y = scaler_rescale(y + 0.5, \
				get_range(RANGE_CLOSED, 0, WINDOW_HEIGHT - 1), \
				get_range(RANGE_CLOSED, height, -height));
	dir.z = 1;
	return (dir);
}

t_tmat	get_transform_matrix(t_vector3 *xs, t_vector3 *ys, \
											t_vector3 *zs, t_vector3 *os)
{
	static double	m[4][3];

	m[0][0] = xs->x;
	m[0][1] = xs->y;
	m[0][2] = xs->z;
	m[1][0] = ys->x;
	m[1][1] = ys->y;
	m[1][2] = ys->z;
	m[2][0] = zs->x;
	m[2][1] = zs->y;
	m[2][2] = zs->z;
	m[3][0] = os->x;
	m[3][1] = os->y;
	m[3][2] = os->z;
	return (m);
}

t_vector3	get_global_ray_dir(t_scene *scene, t_vector3 local)
{
	t_vector3			vup;
	t_vector3			xs;
	t_vector3			ys;
t_tmat	m;

	vup = get_vup(scene->camera.dir);
	xs = v3_cross(vup, scene->camera.dir);
	ys = v3_cross(scene->camera.dir, xs);
	m = get_transform_matrix(&xs, &ys, &scene->camera.dir, \
								&scene->camera.origin);
	return (v3_to_unit(v3_transform(local, m)));
}

t_ray	get_rotated_ray(t_scene *scene, double y, double x)
{
	t_vector3	local;
	t_ray		ray;

	local = get_local_ray_dir(scene, y, x);
	ray.dir = get_global_ray_dir(scene, local);
	ray.origin = scene->camera.origin;
	return (ray);
}
