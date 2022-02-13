/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/13 16:33:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "objects.h"

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
	if (root < 0)
		root = (-d.h + sqrtd) / d.a;
	if (root < 0)
		return (0);
	if (root >= record->distence)
		return (0);
	record->point = v3_add(v3_mul_scaler(ray.dir, root), ray.origin);
	record->normal = v3_to_unit(v3_sub(record->point, sphere->origin));
	record->distence = root;
	record->phong = sphere->phong;
	record->object = sphere;
	return (1);
}

int hit_cylinder()
{

}

#include <stdio.h>
int hit_plane(t_ray ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;
	
	ld = v3_dot(ray.dir, plane->normal);
	if (ld == 0)
	{
//		printf("NOT in plane: %.3lf\n", dist);

		return (0);
	}
	dist = v3_dot(v3_sub(plane->origin, ray.origin), plane->normal) / ld;
	if (dist < 0 || record->distence <= dist)
		return (0);
	record->distence = dist;
	record->point = v3_add(v3_mul_scaler(ray.dir, dist), ray.origin);
	record->normal = plane->normal;
	record->phong = plane->phong;
	record->object = plane;
	return (1);
}

int hit_cone()
{

}

int	hit_object(t_ray ray, t_list *list, t_hit_record *record)
{
	int	hit_something;

	hit_something = 0;
	while (list)
	{
		if (list->type == OBJ_SPHERE)
			hit_something |= hit_sphere(ray, (t_sphere *)list->content, record);
		if (list->type == OBJ_CYLINDER)
			hit_something |= hit_cylinder();
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

	v3_mul_scaler(v3_mul(scene->gl.ambient, record->phong.albedo), scene->gl.ratio);
	while (scene->light_list)
	light_dir = v3_to_unit(v3_sub(record->point, ));
}
*/