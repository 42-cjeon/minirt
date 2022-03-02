/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/02 12:58:59 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

void	get_cylinder_uv(t_cylinder *cylinder, t_hit_record *record, double dd)
{
	t_vector3	k;

	k = record->normal;
	if (record->normal.z == 0)
		k.z = k.y;
	record->shading.u = 0.5 + atan2(k.x, k.z) \
						/ (2 * M_PI);
	record->shading.v = dd / cylinder->height;
	if (cylinder->shading.surf_type == SURF_CB)
	{
		record->shading.u *= 16;
		record->shading.v *= cylinder->height;
	}
}

int	check_cylinder_line_root(const t_ray *ray, t_cylinder *cylinder, \
								double root, t_hit_record *record)
{
	t_vector3	point;
	t_vector3	h;
	t_vector3	pt;
	double		dd;
	double		t;

	if (root <= CAMERA_NEAR || record->distance <= root)
		return (FALSE);
	point = v3_add(v3_mul_scalar(ray->dir, root), ray->origin);
	h = v3_mul_scalar(cylinder->dir, cylinder->height);
	h = v3_sub(v3_add(h, cylinder->origin), cylinder->origin);
	dd = v3_dot(v3_sub(point, cylinder->origin), v3_to_unit(h));
	if (dd < 0 || v3_length(h) < dd)
		return (FALSE);
	record->point = point;
	t = v3_dot(v3_sub(record->point, cylinder->origin), cylinder->dir);
	pt = v3_add(cylinder->origin, v3_mul_scalar(cylinder->dir, t));
	record->normal = v3_to_unit(v3_sub(point, pt));
	record->distance = root;
	record->shading = cylinder->shading;
	get_cylinder_uv(cylinder, record, dd);
	return (TRUE);
}

t_quadratic_eq	get_cylinder_line_eq(const t_ray *ray, t_cylinder *cylinder)
{
	t_quadratic_eq	eq;
	t_vector3		hhat;
	t_vector3		w;

	hhat = v3_mul_scalar(cylinder->dir, cylinder->height);
	hhat = v3_sub(v3_add(hhat, cylinder->origin), cylinder->origin);
	hhat = v3_to_unit(hhat);
	w = v3_sub(ray->origin, cylinder->origin);
	eq.a = v3_dot(ray->dir, ray->dir) \
			- v3_dot(ray->dir, hhat) * v3_dot(ray->dir, hhat);
	eq.hb = v3_dot(ray->dir, w) - v3_dot(ray->dir, hhat) * v3_dot(w, hhat);
	eq.c = v3_dot(w, w) - v3_dot(w, hhat) * v3_dot(w, hhat) \
			- cylinder->radius * cylinder->radius;
	return (eq);
}

int	hit_cylinder(const t_ray *ray, t_cylinder *cylinder, t_hit_record *record)
{
	t_quadratic_eq	eq;
	double			root;

	eq = get_cylinder_line_eq(ray, cylinder);
	if (!quad_has_root(&eq))
		return (FALSE);
	root = quad_get_root(&eq, ROOT_ALPHA);
	if (check_cylinder_line_root(ray, cylinder, root, record))
		return (TRUE);
	root = quad_get_root(&eq, ROOT_BETA);
	if (check_cylinder_line_root(ray, cylinder, root, record))
	{
		record->normal = v3_mul_scalar(record->normal, -1);
		return (TRUE);
	}
	return (FALSE);
}
