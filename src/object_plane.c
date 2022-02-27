/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 17:07:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <assert.h>
#include "scene.h"

#define PLANE_SIZE 10

void	get_plane_uv(const t_ray *ray, t_plane *plane, t_hit_record *record)
{
	t_vector3	nx;
	t_vector3	nz;

	nx = v3_cross(get_vup(plane->dir), plane->dir);
	nz = v3_cross(plane->dir, nx);

	if (plane->shading.surf_type == SURF_CB)
	{
		record->shading.u = fabs(v3_dot(nx, v3_sub(record->point, ray->origin))) + 0.5;
		record->shading.v = fabs(v3_dot(nz, v3_sub(record->point, ray->origin))) + 0.5;
	}
	else
	{
		record->shading.u = v3_dot(nx, v3_sub(record->point, ray->origin)) / PLANE_SIZE;
		record->shading.v = v3_dot(nz, v3_sub(record->point, ray->origin)) / PLANE_SIZE;
		record->shading.u += 1 - (int)record->shading.u;
		record->shading.v += 1 - (int)record->shading.v;
		record->shading.u /= 2;
		record->shading.v /= 2;
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
	get_plane_uv(ray, plane, record);

	return (TRUE);
}
