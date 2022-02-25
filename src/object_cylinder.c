/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/25 12:37:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

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
	point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	h = v3_mul_scaler(cylinder->dir, cylinder->height);
	h = v3_sub(v3_add(h, cylinder->origin), cylinder->origin);
	dd = v3_dot(v3_sub(point, cylinder->origin), v3_to_unit(h));
	if (dd < 0 || v3_length(h) < dd)
		return (FALSE);
	record->point = point;
	t = v3_dot(v3_sub(record->point, cylinder->origin), cylinder->dir);
	pt = v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, t));
	record->normal = v3_to_unit(v3_sub(point, pt));
	record->distance = root;

#ifdef TEXTURE_CB

	int u, v;
	t_vector3 q;
	q = v3_to_unit(v3_sub(record->point, v3_add(v3_mul_scaler(cylinder->dir, dd), cylinder->origin)));

	u = (int)(((0.5 + (atan2(q.x, q.z) / (2 * M_PI)))) * 2 * M_PI * cylinder->radius);
	v = dd;

	if ((u % 2 == 0 && v % 2 == 0) || (u % 2 == 1 && v % 2 == 1))
		record->shading.albedo = (t_color3){1, 1, 1};
	else if  ((u % 2 == 0 && v % 2 == 1) || (u % 2 == 1 && v % 2 == 0))
		record->shading.albedo = (t_color3){0, 0, 0};

#else

	record->shading = cylinder->shading;

#endif

	return (TRUE);
}

t_quadratic_eq	get_cylinder_line_eq(const t_ray *ray, t_cylinder *cylinder)
{
	t_quadratic_eq	eq;
	t_vector3		hhat;
	t_vector3		w;

	hhat = v3_mul_scaler(cylinder->dir, cylinder->height);
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
	int				is_hit;

	eq = get_cylinder_line_eq(ray, cylinder);
	if (!quad_has_root(&eq))
		return (FALSE);
	is_hit = FALSE;
	root = quad_get_root(&eq, ROOT_ALPHA);
	is_hit |= check_cylinder_line_root(ray, cylinder, root, record);
	root = quad_get_root(&eq, ROOT_BETA);
	is_hit |= check_cylinder_line_root(ray, cylinder, root, record);
	return (is_hit);
}
