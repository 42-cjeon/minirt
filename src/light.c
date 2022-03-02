/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 11:35:33 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/02 12:55:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "color.h"
#include "scene.h"
#include "utils.h"
#include "texture.h"

t_color3	phong_shading(t_scene *scene, t_list *light, \
							t_hit_record *record, t_color3 color)
{
	if (light->type == LIG_SPOT)
		return (phong_spot_light(scene, (t_spot_light *)light->content, \
									record, color));
	return (get_vector3(0.5, 0.5, 0.5));
}

t_color3	calc_color(t_scene *scene, t_hit_record *record)
{
	t_list		*light;
	t_color3	surf_color;
	t_color3	mixed_color;

	handle_nmap(scene, record);
	surf_color = get_surf_color(scene, record);
	mixed_color = v3_mul_scalar(v3_mul(surf_color, scene->ambient.color), \
										scene->ambient.ratio);
	light = scene->light_list;
	while (light)
	{
		mixed_color = v3_add(mixed_color, \
							phong_shading(scene, light, record, surf_color));
		light = light->next;
	}
	return (mixed_color);
}
