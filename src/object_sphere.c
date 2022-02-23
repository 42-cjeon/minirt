/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:12 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:34:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	check_sphere_line_root(const t_ray *ray, t_sphere *sphere, \
							double root, t_hit_record *record)
{
	if (root <= CAMERA_NEAR || record->distence <= root)
		return (FALSE);
	record->point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	record->normal = v3_to_unit(v3_sub(record->point, sphere->origin));
	record->distence = root;
	record->shading = sphere->shading;
	return (TRUE);
}

t_quadratic_eq	get_sphere_line_eq(const t_ray *ray, const t_sphere *sphere)
{
	t_quadratic_eq	eq;
	t_vector3		oc;

	oc = v3_sub(ray->origin, sphere->origin);
	eq.a = v3_dot(ray->dir, ray->dir);
	eq.hb = v3_dot(ray->dir, oc);
	eq.c = v3_dot(oc, oc) - sphere->radius * sphere->radius;
	return (eq);
}

int	hit_sphere(const t_ray *ray, t_sphere *sphere, t_hit_record *record)
{
	t_quadratic_eq	eq;
	double			root;
	int				is_hit;

	eq = get_sphere_line_eq(ray, sphere);
	if (!quad_has_root(&eq))
		return (FALSE);
	is_hit = FALSE;
	root = quad_get_root(&eq, ROOT_ALPHA);
	is_hit |= check_sphere_line_root(ray, sphere, root, record);
	root = quad_get_root(&eq, ROOT_ALPHA);
	is_hit |= check_sphere_line_root(ray, sphere, root, record);
	return (is_hit);
}
