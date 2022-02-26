/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:51 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/26 15:52:32 by cjeon            ###   ########.fr       */
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
	if (parse_double(ignore_space(context), get_named_range(RNG_POS), &scene->camera.focal_len))
		return (throw_error(context, "camera->focal_length", P_T_POS));
	scene->camera.fov_w = scene->camera.fov_w / 180 * M_PI;
	return (parse_endl(context));
}
