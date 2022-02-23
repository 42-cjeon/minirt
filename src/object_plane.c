/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:07 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 22:52:00 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	hit_plane(const t_ray *ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;

	ld = v3_dot(ray->dir, plane->dir);
	if (ld == 0)
		return (FALSE);
	dist = v3_dot(v3_sub(plane->origin, ray->origin), plane->dir) / ld;
	if (dist <= CAMERA_NEAR || record->distence <= dist)
		return (FALSE);
	record->distence = dist;
	record->point = v3_add(v3_mul_scaler(ray->dir, dist), ray->origin);
	if (v3_dot(ray->dir, plane->dir) < 0)
		record->normal = plane->dir;
	else
		record->normal = v3_mul_scaler(plane->dir, -1);
	record->shading = plane->shading;
	return (TRUE);
}
