/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:51 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 14:55:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "parser.h"

int	parse_camera(t_context *context)
{
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_INF), &context->scene->camera.origin))
		return (throw_error(context, "camera->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_UNITV), &context->scene->camera.dir) \
		|| v3_equal(context->scene->camera.dir, get_vector3(0, 0, 0)))
		return (throw_error(context, "camera->dir", P_T_UNITV));
	context->scene->camera.dir = v3_to_unit(context->scene->camera.dir);
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_FOV), &context->scene->camera.fov_w))
		return (throw_error(context, "camera->fov", P_T_FOV));
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_POS), &context->scene->camera.focal_len))
		return (throw_error(context, "camera->focal_length", P_T_POS));
	context->scene->camera.fov_w = context->scene->camera.fov_w / 180 * M_PI;
	return (parse_endl(context));
}
