/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 00:56:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

void	get_plane_uv(t_plane *plane, t_hit_record *record)
{
	t_vector3	nx;
	t_vector3	nz;
	//t_vector3	d;

	nx = get_vup(plane->dir);
	nz = v3_cross(nx, plane->dir);

	//d = v3_sub(record->point, plane->origin);
	if (plane->shading.surf_type == SURF_CB)
	{
		record->shading.u = fabs(v3_dot(nx, record->point)) + 0.5;
		record->shading.v = fabs(v3_dot(nz, record->point)) + 0.5;
	}
	else
	{
		record->shading.u = fabs(v3_dot(nx, record->point)) + 0.5;
		record->shading.v = fabs(v3_dot(nz, record->point)) + 0.5;
	}
}

int	hit_plane(const t_ray *ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;

	ld = v3_dot(ray->dir, plane->dir);
	if (ld == 0)
		return (FALSE);
	dist = v3_dot(v3_sub(plane->origin, ray->origin), plane->dir) / ld;
	if (dist <= CAMERA_NEAR || record->distance <= dist)
		return (FALSE);
	record->distance = dist;
	record->point = v3_add(v3_mul_scaler(ray->dir, dist), ray->origin);
	if (v3_dot(ray->dir, plane->dir) < 0)
		record->normal = plane->dir;
	else
		record->normal = v3_mul_scaler(plane->dir, -1);
	record->shading = plane->shading;
	get_plane_uv(plane, record);

	return (TRUE);
}
