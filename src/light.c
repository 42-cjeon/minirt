/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:35:33 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:23:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "scene.h"
#include "utils.h"

static int	is_in_shadow(const t_ray *ray, t_list *objs, double dist)
{
	t_hit_record	record;

	if (hit_object(ray, objs, &record) && record.distence < dist)
		return (1);
	return (0);
}

static t_color3	phong_point_light(t_list *objs, t_point_light *light, \
								t_hit_record *record)
{
	t_ray		ray;
	double		dist;
	double		cos_theta;
	t_color3	color;

	ft_memset(&color, 0, sizeof(t_color3));
	ray.origin = record->point;
	ray.dir = v3_sub(light->origin, record->point);
	dist = v3_length(ray.dir);
	ray.dir = v3_to_unit(ray.dir);
	if (is_in_shadow(&ray, objs, dist))
		return (get_vector3(0, 0, 0));
	cos_theta = v3_dot(ray.dir, record->normal);
	if (cos_theta < 0.0)
		cos_theta = 0;
	color = v3_mul(light->color, record->shading.albedo);
	color = v3_mul_scaler(color, light->ratio * cos_theta);
	color = v3_mul_scaler(color, 1 / (1.0 + C1 * dist + C2 * dist * dist));
	return (color);
}

t_color3	phong_shading(t_list *objs, t_list	*light, t_hit_record *record)
{
	if (light->type == LIG_POINT)
		return (phong_point_light(objs, light->content, record));
	return (get_vector3(0, 0, 0));
}

t_color3	calc_color(t_scene *scene, t_hit_record *record)
{
	t_list		*light;
	t_color3	color;

	color = v3_mul(scene->ambient.color, record->shading.albedo);
	color = v3_mul_scaler(color, scene->ambient.ratio);
	light = scene->light_list;
	while (light)
	{
		color = v3_add(color, phong_shading(scene->obj_list, light, record));
		light = light->next;
	}
	return (color);
}
