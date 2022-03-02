/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:24:20 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/02 12:55:52 by cjeon            ###   ########.fr       */
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

t_color3	phong_spot_specular(t_scene *scene, t_spot_light *light, \
								t_hit_record *record, t_ray *ray)
{
	t_vector3	refl;
	t_color3	spec;
	double		ratio;

	refl = v3_to_unit(v3_reflect(ray->dir, record->normal));
	ratio = -v3_dot(refl, \
			v3_to_unit(v3_sub(record->point, scene->camera.origin)));
	if (0 < ratio)
		spec = v3_mul_scalar(light->color, \
					pow(ratio, record->shading.kss) * record->shading.ks);
	else
		spec = get_vector3(0, 0, 0);
	return (spec);
}

t_color3	phong_spot_diffuse(t_ray *ray, t_spot_light *light, \
								t_hit_record *record)
{
	double		cos_theta;

	cos_theta = -v3_dot(ray->dir, light->dir);
	if (cos_theta <= cos(light->theta))
		return (get_vector3(0, 0, 0));
	cos_theta = v3_dot(ray->dir, record->normal);
	if (cos_theta <= 0.0)
		return (get_vector3(0, 0, 0));
	return (v3_mul_scalar(light->color, cos_theta));
}

t_color3	phong_spot_light(t_scene *scene, t_spot_light *light, \
								t_hit_record *record, t_color3 surf_color)
{
	t_ray		ray;
	double		dist;
	t_color3	color;
	t_color3	diffuse;
	t_color3	specular;

	ray.origin = record->point;
	ray.dir = v3_sub(light->origin, record->point);
	dist = v3_length(ray.dir);
	ray.dir = v3_to_unit(ray.dir);
	diffuse = phong_spot_diffuse(&ray, light, record);
	if (v3_equal(diffuse, get_vector3(0, 0, 0)))
		return (get_vector3(0, 0, 0));
	if (is_in_shadow(&ray, scene->obj_list, dist))
		return (get_vector3(0, 0, 0));
	specular = phong_spot_specular(scene, light, record, &ray);
	color = v3_mul(v3_add(diffuse, specular), surf_color);
	color = v3_mul_scalar(color, light->ratio);
	color = v3_mul_scalar(color, \
					1 / (1.0 + scene->kld * dist + scene->kldd * dist * dist));
	return (color);
}
