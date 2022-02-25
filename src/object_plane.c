/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/25 12:36:30 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

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

#ifdef TEXTURE_CB

	int u, v;

	t_vector3 nx = get_vup(plane->dir);
	t_vector3 nz = v3_cross(nx, plane->dir);
	u = fabs(v3_dot(nx, record->point)) + 0.5;
	v = fabs(v3_dot(nz, record->point)) + 0.5;

	if ((u % 2 == 0 && v % 2 == 0) || (u % 2 == 1 && v % 2 == 1))
		record->shading.albedo = (t_color3){1, 1, 1};
	else if  ((u % 2 == 0 && v % 2 == 1) || (u % 2 == 1 && v % 2 == 0))
		record->shading.albedo = (t_color3){0, 0, 0};

#else
		
	record->shading = plane->shading;

#endif

	return (TRUE);
}
