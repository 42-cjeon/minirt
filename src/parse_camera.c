/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:51 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 22:53:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "parser.h"

int	parse_camera(char *line, t_scene *scene)
{
	line = parse_vector3(ignore_space(line), get_named_range(RNG_INF), \
							&scene->camera.origin);
	if (line == NULL)
		return (1);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_UNITV), \
							&scene->camera.dir);
	if (line == NULL)
		return (1);
	line = parse_double(ignore_space(line), get_named_range(RNG_FOV), \
							&scene->camera.fov_w);
	if (line == NULL)
		return (1);
	scene->camera.fov_w = scene->camera.fov_w / 180 * M_PI;
	scene->camera.fov_h = scene->camera.fov_w * WINDOW_HEIGHT / WINDOW_WIDTH;
	return (parse_endl(line));
}
