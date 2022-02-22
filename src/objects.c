/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 02:48:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "scene.h"

typedef struct s_quadratic_eq
{
	double	a;
	double	hb;
	double	c;
	double	d;
}	t_quadratic_eq;

enum e_root_type
{
	ROOT_ALPHA,
	ROOT_BETA
};

int quad_has_root(t_quadratic_eq *eq)
{
	eq->d = eq->hb * eq->hb - eq->a * eq->c;
	if (0 <= eq->d)
		return (TRUE);
	return (FALSE);
}

double	quad_get_root(const t_quadratic_eq *eq, enum e_root_type type)
{
	if (type == ROOT_ALPHA)
		return ((-eq->hb - sqrt(eq->d)) / eq->a);
	if (type == ROOT_BETA)
		return ((-eq->hb + sqrt(eq->d)) / eq->a);
	return (NAN);
}

int	check_sphere_line_root(const t_ray *ray, t_sphere *sphere, double root, t_hit_record *record)
{
	if (!is_in_range(root, get_range(RANGE_OPEN, CAMERA_NEAR, record->distence)))
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

int check_cylinder_line_root(const t_ray *ray, t_cylinder *cylinder, double root, t_hit_record *record)
{
	t_vector3	point;
	t_vector3	h;
	t_vector3	pt;
	double		dd;
	double		t;

	if (!is_in_range(root, get_range(RANGE_OPEN, CAMERA_NEAR, record->distence)))
		return (FALSE);
	point = v3_add(v3_mul_scaler(ray->dir, root), ray->origin);
	h = v3_sub(v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, cylinder->height)), cylinder->origin);
	dd = v3_dot(v3_sub(point, cylinder->origin), v3_to_unit(h));
	if (dd < 0 ||  v3_length(h) < dd)
		return (FALSE);
	record->point = point;
	t = v3_dot(v3_sub(record->point, cylinder->origin), cylinder->dir);
	pt = v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, t));
	record->normal = v3_to_unit(v3_sub(point, pt));
	record->distence = root;
	record->shading = cylinder->shading;
	return (TRUE);
	
}

t_quadratic_eq	get_cylinder_line_eq(const t_ray *ray, t_cylinder *cylinder)
{
	t_quadratic_eq	eq;
	t_vector3		hhat;
	t_vector3		w;

	hhat = v3_to_unit(v3_sub(v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, cylinder->height)), cylinder->origin));
	w = v3_sub(ray->origin, cylinder->origin);
	eq.a = v3_dot(ray->dir, ray->dir) - v3_dot(ray->dir, hhat) * v3_dot(ray->dir, hhat);
	eq.hb =  v3_dot(ray->dir, w) - v3_dot(ray->dir, hhat) * v3_dot(w, hhat);
	eq.c = v3_dot(w, w) - v3_dot(w, hhat) * v3_dot(w, hhat) - cylinder->radius * cylinder->radius;
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

int hit_plane(const t_ray *ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;
	
	ld = v3_dot(ray->dir, plane->dir);
	if (ld == 0)
		return (0);
	dist = v3_dot(v3_sub(plane->origin, ray->origin), plane->dir) / ld;
	if (dist <= CAMERA_NEAR || record->distence <= dist)
		return (0);
	record->distence = dist;
	record->point = v3_add(v3_mul_scaler(ray->dir, dist), ray->origin);
	if (v3_dot(ray->dir, plane->dir) < 0)
		record->normal = plane->dir;
	else
		record->normal = v3_mul_scaler(plane->dir, -1);
	record->shading = plane->shading;
	return (1);
}

int hit_cone()
{

}

int	hit_object(const t_ray *ray, t_list *list, t_hit_record *record)
{
	int	hit_something;

	record->distence = CAMERA_FAR;
	hit_something = 0;
	while (list)
	{
		if (list->type == OBJ_SPHERE)
			hit_something |= hit_sphere(ray, (t_sphere *)list->content, record);
		if (list->type == OBJ_CYLINDER)
			hit_something |= hit_cylinder(ray, (t_cylinder *)list->content, record);
		if (list->type == OBJ_PLANE)
			hit_something |= hit_plane(ray, (t_plane *)list->content, record);
		if (list->type == OBJ_CONE)
			hit_something |= hit_cone();
		list = list->next;
	}
	return (hit_something);
}
/*
t_color3	get_object_color(t_scene *scene, t_hit_record *record)
{
	t_color3	color;
	t_vector3	light_dir;

	v3_mul_scaler(v3_mul(scene->gl.ambient, record->shading.albedo), scene->gl.ratio);
	while (scene->light_list)
	light_dir = v3_to_unit(v3_sub(record->point, ));
}
*/