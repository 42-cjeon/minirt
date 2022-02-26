/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:01:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/26 20:26:45 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "scene.h"
#include "color.h"
#include "utils.h"

static uint32_t	get_pixel_color(t_scene *scene, const t_ray *ray, double y)
{
	t_hit_record			record;
	t_color3				color_vec;
	const static t_color3	skybox[2] = {
		{0.5, 0.7, 1},
		{1, 1, 1}
	};

	if (hit_object(ray, scene->obj_list, &record))
		color_vec = calc_color(scene, &record);
	else
		color_vec = v3_lerp(skybox[0], skybox[1], y / scene->window_height);
	return (v3_to_color(color_vec));
}

int	draw_scene(t_window *window, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;
	uint32_t	*img;

	img = window->image.data;
	i = 0;
	while (i < scene->window_height)
	{
		j = 0;
		while (j < scene->window_width)
		{
			ray = get_rotated_ray(scene, i, j);
			*img = get_pixel_color(scene, &ray, i);
			img++;
			j++;
		}
		i++;
	}
	return (0);
}
