/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:12 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 16:07:05 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "color.h"
#include "scene.h"

/* NMAP
	uint32_t bump_map = nmap.data[(int)(v * (nmap.height - 1)) * nmap.width + (int)(u * (nmap.width - 1))];
	t_vector3 bm = v3_to_unit(v3_sub_scaler(v3_mul_scaler(color_to_v3(bump_map), 2), 1));
	t_vector3	tn = v3_cross(get_vup(record->normal), record->normal);
	t_vector3	bi = v3_cross(record->normal, tn);
	record->normal = v3_transform(bm, get_transform_matrix(&tn, &bi, &record->normal, &(t_vector3){0, 0, 0}));
	record->normal = v3_to_unit(record->normal);
*/

/* CB
	if ((u % 2 == 0 && v % 2 == 0) || (u % 2 == 1 && v % 2 == 1))
		record->shading.albedo = (t_color3){1, 1, 1};
	else if  ((u % 2 == 0 && v % 2 == 1) || (u % 2 == 1 && v % 2 == 0))
		record->shading.albedo = (t_color3){0, 0, 0};
*/
#include <stdio.h>
void	get_sphere_uv(t_sphere *sphere, t_hit_record *record)
{
	record->shading.u = (0.5 + (atan2(record->normal.x, record->normal.z) / (2 * M_PI)));
	record->shading.v = (0.5 - (asin(record->normal.y) / M_PI));
	if (sphere->shading.surf_type == SURF_CB)
	{
		record->shading.u *= 16;
		record->shading.v *= 8;
	}
}

int	check_sphere_line_root(const t_ray *ray, t_sphere *sphere, \
							double root, t_hit_record *record)
{
	if (root <= CAMERA_NEAR || record->distance <= root)
		return (FALSE);
	record->point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	record->normal = v3_to_unit(v3_sub(record->point, sphere->origin));
	record->distance = root;
	record->shading = sphere->shading;
	get_sphere_uv(sphere, record);

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

	eq = get_sphere_line_eq(ray, sphere);
	if (!quad_has_root(&eq))
		return (FALSE);
	root = quad_get_root(&eq, ROOT_ALPHA);
	if (check_sphere_line_root(ray, sphere, root, record))
		return (TRUE);
	root = quad_get_root(&eq, ROOT_BETA);
	if (check_sphere_line_root(ray, sphere, root, record))
	{
		record->normal = v3_mul_scaler(record->normal, -1);
		return (TRUE);
	}
	return (FALSE);
}
