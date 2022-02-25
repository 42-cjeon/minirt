/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:12 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/25 12:35:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"

int	check_sphere_line_root(const t_ray *ray, t_sphere *sphere, \
							double root, t_hit_record *record)
{
	if (root <= CAMERA_NEAR || record->distance <= root)
		return (FALSE);
	record->point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	record->normal = v3_to_unit(v3_sub(record->point, sphere->origin));
	record->distance = root;

	t_vector3	p = v3_to_unit(v3_sub(record->point, sphere->origin));

#ifdef TEXTURE_CB

	int u, v;

	u = (int)((0.5 + (atan2(p.x, p.z) / (2 * M_PI))) * M_PI * sphere->radius);
	v = (int)((0.5 - (asin(p.y) / M_PI)) * M_PI * sphere->radius);
	//printf("u=%d v=%d\n", u, v);
	if ((u % 2 == 0 && v % 2 == 0) || (u % 2 == 1 && v % 2 == 1))
		record->shading.albedo = (t_color3){1, 1, 1};
	else if  ((u % 2 == 0 && v % 2 == 1) || (u % 2 == 1 && v % 2 == 0))
		record->shading.albedo = (t_color3){0, 0, 0};

#else

	record->shading = sphere->shading;

#endif

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
