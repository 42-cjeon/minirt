/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:24:20 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 01:02:12 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene.h"
#include "light.h"

static int	is_in_shadow(const t_ray *ray, t_list *objs, double dist)
{
	t_hit_record	record;

	if (hit_object(ray, objs, &record) && record.distance < dist)
		return (1);
	return (0);
}

t_color3	phong_spot_light(t_scene *scene, t_spot_light *light, \
								t_hit_record *record, t_color3 color)
{
	t_ray		ray;
	double		dist;
	double		cos_theta;
	t_color3	diffuse;
	t_color3	specular;

	ft_memset(&color, 0, sizeof(t_color3));
	ray.origin = record->point;
	ray.dir = v3_sub(light->origin, record->point);
	dist = v3_length(ray.dir);
	ray.dir = v3_to_unit(ray.dir);
	if (is_in_shadow(&ray, scene->obj_list, dist))
		return (get_vector3(0, 0, 0));
	cos_theta = v3_dot(v3_to_unit(v3_sub(record->point, light->origin)), light->dir);
	if (cos_theta < cos(light->theta))
		return (get_vector3(0, 0, 0));
	cos_theta = v3_dot(ray.dir, record->normal);
	if (cos_theta < 0.0)
		return (get_vector3(0, 0, 0));
	
	diffuse = v3_mul(color, light->color);
	diffuse = v3_mul_scaler(color, cos_theta);
	
	t_vector3 refl = v3_reflect(ray.dir, record->normal);
	double l = v3_dot(refl, v3_to_unit(record->point));
	specular = get_vector3(0, 0, 0);
	if (l < 0)
	{
		specular = v3_mul(color, light->color);;
		specular = v3_mul_scaler(specular, pow(-l, record->shading.kss) * record->shading.ks);
	}
	color = v3_mul_scaler(v3_add(diffuse, specular), 1 / (1.0 + scene->kld * dist + scene->kldd * dist * dist));
	return (color);
}