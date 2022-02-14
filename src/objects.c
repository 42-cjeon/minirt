/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/14 17:55:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit_record *record)
{
	// LINE : P = L0 + tv;
	// cy   : (P - C)^2 = (Q - C)^2 + r^2
	// h_hat = cy.dir;
	double		a;
	double		hb;
	double		c;
	double		d;
	double		sqrtd;
	double		root;
	t_vector3	w;

	w = v3_sub(ray.origin, cylinder->origin);
	a = v3_dot(ray.dir, ray.dir) - v3_dot(ray.dir, cylinder->dir) * v3_dot(ray.dir, cylinder->dir);
	hb = v3_dot(ray.dir, w) - v3_dot(ray.dir, cylinder->dir) * v3_dot(w, cylinder->dir);
	c = v3_dot(w, w) - v3_dot(w, cylinder->dir) * v3_dot(w, cylinder->dir) - cylinder->diameter;
	d = hb * hb - a * c;
	if (d < 0)
		return (0);
	sqrtd = sqrt(d);
	root = (-hb - sqrtd) / a;
	if (root < 0)
		root = (-hb + sqrtd) / a;
	if (root < 0)
		return (0);
	if (root >= record->distence)
		return (0);
	t_vector3 point = v3_add(v3_mul_scaler(ray.dir, root), ray.origin);
	t_vector3 h = v3_add(v3_mul_scaler(cylinder->dir, cylinder->height), cylinder->origin);
	double dd = v3_dot(v3_sub(point, cylinder->origin), h);
	/*
	if (dd < 0 || v3_length(h) < dd)
	{
	  
	}
	*/
	record->point = point;
	t_vector3 cc = v3_mul_scaler(h, 0.5);
	double t = v3_dot(v3_sub(record->point, cylinder->origin), cylinder->dir);
	t_vector3 pt = v3_add(cylinder->origin, v3_mul_scaler(cylinder->dir, t));
	record->normal = v3_to_unit(v3_sub(point, pt));
	record->distence = root;
	record->phong = cylinder->phong;
	record->object = cylinder;
	return (1);
}

#include <stdio.h>
int hit_plane(t_ray ray, t_plane *plane, t_hit_record *record)
{
	double	dist;
	double	ld;
	
	ld = v3_dot(ray.dir, plane->normal);
	if (ld == 0)
		return (0);
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

	v3_mul_scaler(v3_mul(scene->gl.ambient, record->phong.albedo), scene->gl.ratio);
	while (scene->light_list)
	light_dir = v3_to_unit(v3_sub(record->point, ));
}
*/