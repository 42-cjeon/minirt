/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 00:48:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (1);
}

int hit_cylinder()
{

}

int hit_plane()
{

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
			hit_something |= hit_sphere(ray, list->content, record);
		if (list->type == OBJ_CYLINDER)
			hit_something |= hit_cylinder();
		if (list->type == OBJ_PLANE)
			hit_something |= hit_plane();
		if (list->type == OBJ_CONE)
			hit_something |= hit_cone();
		list = list->next;
	}
	return (hit_something);
}