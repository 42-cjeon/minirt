/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 00:51:48 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "scene.h"

typedef struct s_discriminant
{
	t_vector3	oc;
	double		a;
	double		h;
	double		c;
	double		d;
}	t_discriminant;

int hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *record)
{
	t_discriminant	d;
	double			sqrtd;
	double			root;

	d.oc = v3_sub(ray.origin, sphere->origin);
	d.a = v3_dot(ray.dir, ray.dir);
	d.h = v3_dot(ray.dir, d.oc);
	d.c = v3_dot(d.oc, d.oc) - sphere->radius * sphere->radius;
	d.d = d.h * d.h - d.a * d.c;
	if (d.d < 0)
		return (0);
	sqrtd = sqrt(d.d);
	root = (-d.h - sqrtd) / d.a;
	if (root <= CAMERA_NEAR)
		root = (-d.h + sqrtd) / d.a;
	if (root <= CAMERA_NEAR)
		return (0);
	if (root >= record->distence)
		return (0);
	record->point = v3_add(v3_mul_scaler(ray.dir, root), ray.origin);
	record->normal = v3_to_unit(v3_sub(record->point, sphere->origin));
	record->distence = root;
	record->shading = sphere->shading;
	return (1);
}

int check_root(double root, t_ray ray, t_cylinder *cylinder, t_hit_record *record)
{
	if (root <= CAMERA_NEAR)
		return (0);
	if (record->distence <= root)
		return (0);
	t_vector3 point = v3_add(v3_mul_scaler(ray.dir, root), ray.origin);
	t_vector3 h = v3_sub(v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, cylinder->height)), cylinder->origin);
	double dd = v3_dot(v3_sub(point, cylinder->origin), v3_to_unit(h));
	//printf("dd = %.3lf\n", dd);
	if (dd < 0 ||  v3_length(h) < dd)
		return (0);
	record->point = point;
	double t = v3_dot(v3_sub(record->point, cylinder->origin), cylinder->dir);
	t_vector3 pt = v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, t));
	record->normal = v3_to_unit(v3_sub(point, pt));
	record->distence = root;
	record->shading = cylinder->shading;
	return (1);
	
}

int	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit_record *record)
{
	t_vector3	h;
	t_vector3	w;

	double a, b, c, d, root;

	h = v3_to_unit(v3_sub(v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, cylinder->height)), cylinder->origin));
	w = v3_sub(ray.origin, cylinder->origin);
	a = v3_dot(ray.dir, ray.dir) - v3_dot(ray.dir, h) * v3_dot(ray.dir, h);
	b =  2 * (v3_dot(ray.dir, w) - v3_dot(ray.dir, h) * v3_dot(w, h));
	c = v3_dot(w, w) - v3_dot(w, h) * v3_dot(w, h) - cylinder->radius * cylinder->radius;

	d = b * b - 4 * a * c;
	if (d < 0) // there is no root
		return (0);
	
	int result = 0;

	root = (-b - sqrt(d)) / (2 * a);
	result |= check_root(root, ray, cylinder, record);
	root = (-b + sqrt(d)) / (2 * a);
	result |= check_root(root, ray, cylinder, record);
	return (result);
}

int hit_plane(t_ray ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;
	
	ld = v3_dot(ray.dir, plane->dir);
	if (ld == 0)
		return (0);
	dist = v3_dot(v3_sub(plane->origin, ray.origin), plane->dir) / ld;
	if (dist <= CAMERA_NEAR || record->distence <= dist)
		return (0);
	record->distence = dist;
	record->point = v3_add(v3_mul_scaler(ray.dir, dist), ray.origin);
	if (v3_dot(ray.dir, plane->dir) < 0)
		record->normal = plane->dir;
	else
		record->normal = v3_mul_scaler(plane->dir, -1);
	record->shading = plane->shading;
	return (1);
}

int hit_cone()
{

}

int	hit_object(t_ray ray, t_list *list, t_hit_record *record)
{
	int	hit_something;

	record->distence = INFINITY;
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