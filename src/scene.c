/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:01:22 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 01:02:20 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"
#include "scene.h"
#include "ray.h"
#include "color.h"

uint32_t	get_pixel_color(t_scene *scene, t_ray ray, double y, double x)
{
	t_hit_record	record;
	t_color3		color_vec;

	record.distence = INFINITY;
	if (hit_object(ray, scene->obj_list, &record))
		color_vec = get_object_color(&record);
	else
		color_vec = v3_lerp((t_vector3){0.5, 0.7, 1.0}, (t_vector3){1, 1, 1}, y / WINDOW_H);
	return (v3_to_color(color_vec));
}

t_ray	get_rotated_ray(const t_scene *scene, double y, double x)
{
	t_ray			ray;
	const t_vector3	angle = {
		0, \
		(scene->camera.fov_h / 2) \
		- (scene->camera.fov_h * (y / WINDOW_HEIGHT)), \
		(scene->camera.fov_w * (x / WINDOW_WIDTH)) \
		- (scene->camera.fov_w / 2)
	};
	ray = scene->camera.ray;
	ray.dir = v3_rotate(ray.dir, angle);
	return (ray);
}

int	draw_scene(t_window *window, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;
	uint32_t	*img;

	img = window->image.img_ptr;
	i = 0;
	j = 0;
	while (i < WINDOW_HEIGHT)
	{
		while(j < WINDOW_WIDTH)
		{
			ray = get_rotated_ray(scene, i, j);
			*img = get_pixel_color(scene, ray);
			img++;
			j++;
		}
		i++;
	}
}