/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/01 18:25:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <math.h>

#include "scene.h"

void	get_cone_uv(t_cone *cone, t_hit_record *record, double dd)
{
	record->shading.u = 0.5 + atan2(record->normal.x, record->normal.z) \
						/ (2 * M_PI);
	record->shading.v = dd / cone->height;
	if (cone->shading.surf_type == SURF_CB)
	{
		record->shading.u *= 16;
		record->shading.v *= cone->height;
	}
}

int	check_cone_line_root(const t_ray *ray, t_cone *cone, \
								double root, t_hit_record *record)
{
	t_vector3	point;
	t_vector3	h;
	t_vector3	op;
	t_vector3	biop;
	double		dd;

	if (root <= CAMERA_NEAR || record->distance <= root)
		return (FALSE);
	point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	h = v3_add(v3_mul_scaler(cone->dir, cone->height), cone->origin);
	dd = -v3_dot(v3_sub(point, h), cone->dir);
	if (dd < 0 || cone->height < dd)
		return (FALSE);
	record->point = point;
	op = v3_sub(record->point, cone->origin);
	biop = v3_cross(op, v3_sub(record->point, v3_add(cone->origin, v3_mul_scaler(cone->dir, dd))));
	op = v3_cross(biop, op);
	if (v3_equal(op, get_vector3(0, 0, 0)))
		record->normal = v3_mul_scaler(cone->dir, -1);
	else
		record->normal = v3_to_unit(op);
	record->distance = root;
	record->shading = cone->shading;
	get_cone_uv(cone, record, dd);
	return (TRUE);
}

t_quadratic_eq	get_cone_line_eq(const t_ray *ray, t_cone *cone)
{
	t_quadratic_eq	eq;
	t_vector3		h;
	t_vector3		w;
	double			m;

	h = v3_mul_scaler(cone->dir, cone->height);
	w = v3_sub(ray->origin, cone->origin);
	m = (cone->radius * cone->radius) / (cone->height * cone->height);
	
	eq.a = v3_dot(ray->dir, ray->dir) - m * v3_dot(ray->dir, cone->dir) * v3_dot(ray->dir, cone->dir) - v3_dot(ray->dir, cone->dir) * v3_dot(ray->dir, cone->dir);
	eq.hb = v3_dot(ray->dir, w) - m * v3_dot(ray->dir, cone->dir) * v3_dot(w, cone->dir) - v3_dot(ray->dir, cone->dir) * v3_dot(w, cone->dir);
	eq.c = v3_dot(w, w) - m * v3_dot(w, cone->dir) * v3_dot(w, cone->dir) - v3_dot(w, cone->dir) * v3_dot(w, cone->dir);
	return (eq);
}

int	hit_cone(const t_ray *ray, t_cone *cone, t_hit_record *record)
{
	t_quadratic_eq	eq;
	double			root;

	eq = get_cone_line_eq(ray, cone);
	if (!quad_has_root(&eq))
		return (FALSE);
	root = quad_get_root(&eq, ROOT_ALPHA);
	if (check_cone_line_root(ray, cone, root, record))
		return (TRUE);
	root = quad_get_root(&eq, ROOT_BETA);
	if (check_cone_line_root(ray, cone, root, record))
	{
		record->normal = v3_mul_scaler(record->normal, -1);
		return (TRUE);
	}
	return (FALSE);
}