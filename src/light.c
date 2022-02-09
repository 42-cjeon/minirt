/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:35:33 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 15:36:49 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "objects.h"
#include "color.h"
t_color3	phong_spot_light(t_list *objs, t_spot_light *light, t_hit_record *record)
{
	return ((t_color3){0, 1, 1});
}

t_color3	phong_point_light(t_list *objs, t_point_light *light, t_hit_record *record)
{
	t_hit_record	shadow_record;
	t_ray			ray;
	double			dist;
	double			cos_theta;
	t_color3		color;

	ft_memset(&color, 0, sizeof(t_color3));
	ray.origin = record->point;
	ray.dir = v3_sub(light->origin, record->point);
	dist = v3_length(ray.dir);
	ray.dir = v3_to_unit(ray.dir);
	
	//blocked by object;
	if (hit_object(ray, objs, &shadow_record) && shadow_record.object != record->object && shadow_record.distence < dist)
		return ((t_color3){0, 0, 0});
	cos_theta = v3_dot(ray.dir, record->normal);
	if (cos_theta < 0.0)
		cos_theta = 0;
	color = v3_mul_scaler(v3_mul(light->color, record->phong.albedo), light->ratio);
	trunc_color(&color);
	return (color);
}

t_color3	phong_shading(t_list *objs, t_list	*light, t_hit_record *record)
{
	if (light->type == LIG_POINT)
		return (phong_point_light(objs, light->content, record));
	else if (light->type == LIG_SPOT)
		return (phong_spot_light(objs, light->content, record));
	return ((t_color3){0, 0, 0});
}

t_color3	calc_color(t_scene *scene, t_hit_record *record)
{
	t_list		*light;
	t_color3	color;

	ft_memset(&color, 0, sizeof(t_color3));
	light = scene->light_list;
	while (light)
	{
		v3_add(color, phong_shading(scene->obj_list, light, record));
		light = light->next;
	}
	return (color);
}