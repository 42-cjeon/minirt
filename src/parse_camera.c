/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:51 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:14:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "parser.h"

int	parse_camera(t_context *context, t_scene *scene)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&scene->camera.origin))
		return (throw_error(context, "camera->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_UNITV), \
						&scene->camera.dir))
		return (throw_error(context, "camera->dir", P_T_UNITV));
	if (parse_double(ignore_space(context), get_named_range(RNG_FOV), \
						&scene->camera.fov_w))
		return (throw_error(context, "camera->fov", P_T_FOV));
	scene->camera.fov_w = scene->camera.fov_w / 180 * M_PI;
	scene->camera.fov_h = scene->camera.fov_w * WINDOW_HEIGHT / WINDOW_WIDTH;
	return (parse_endl(context));
}
