/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:48 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:14:55 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

int	parse_ambient(t_context *context, t_scene *scene)
{
	if (parse_double(ignore_space(context), get_named_range(RNG_RATIO), \
						&scene->ambient.ratio))
		return (throw_error(context, "ambient->ratio", P_T_RATIO));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&scene->ambient.color))
		return (throw_error(context, "ambient->color", P_T_COLOR));
	scene->ambient.color = v3_rescale(scene->ambient.color, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_RATIO));
	return (parse_endl(context));
}

static int	parse_point_light_fail(t_point_light *pl)
{
	free(pl);
	return (P_ERR_SYNTEX);
}

static int	parse_point_light_part(t_context *context, t_point_light *pl)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&pl->origin))
		return (throw_error(context, "pointlight->origin", P_T_POINT));
	if (parse_double(ignore_space(context), get_named_range(RNG_RATIO), \
						&pl->ratio))
		return (throw_error(context, "pointlight->ratio", P_T_RATIO));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&pl->color))
		return (throw_error(context, "pointlight->color", P_T_COLOR));
	return (P_SUCCESS);
}

int	parse_point_light(t_context *context, t_scene *scene)
{
	t_point_light	*pl;
	t_list			*node;

	pl = malloc(sizeof(t_point_light));
	if (pl == NULL)
		return (P_ERR_SYSCALL);
	if (parse_point_light_part(context, pl))
		return (parse_point_light_fail(pl));
	node = ft_lstnew(LIG_POINT, pl);
	if (node == NULL)
	{
		free(pl);
		return (P_ERR_SYSCALL);
	}
	pl->color = v3_rescale(pl->color, \
							get_named_range(RNG_COLOR), \
							get_named_range(RNG_RATIO));
	ft_lstadd_front(&scene->light_list, node);
	return (parse_endl(context));
}
