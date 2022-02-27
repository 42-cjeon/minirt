/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:48 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 15:51:45 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "parser.h"

int	parse_ambient(t_context *context)
{
	if (parse_double(ignore_space(context), get_named_range(RNG_RATIO), \
						&context->scene->ambient.ratio))
		return (throw_error(context, "ambient->ratio", P_T_RATIO));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&context->scene->ambient.color))
		return (throw_error(context, "ambient->color", P_T_COLOR));
	context->scene->ambient.color = \
		v3_rescale(context->scene->ambient.color, \
			get_named_range(RNG_COLOR), \
			get_named_range(RNG_RATIO));
	return (parse_endl(context));
}

static int	parse_spot_light_fail(t_list *node, t_spot_light *sl, int result)
{
	free(sl);
	free(node);
	return (result);
}

static int	parse_spot_light_part(t_context *context, t_spot_light *sl)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&sl->origin))
		return (throw_error(context, "spotlight->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_UNITV), &sl->dir))
		return (throw_error(context, "spotlight->dir", P_T_UNITV));
	sl->dir = v3_to_unit(sl->dir);
	if (parse_double(ignore_space(context), get_range(RANGE_CLOSED, 0, 180), &sl->theta))
		return (throw_error(context, "spotlight->theta", P_T_FOV));
	sl->theta = sl->theta / 180 * M_PI;
	if (parse_double(ignore_space(context), get_named_range(RNG_RATIO), \
						&sl->ratio))
		return (throw_error(context, "spotlight->ratio", P_T_RATIO));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&sl->color))
		return (throw_error(context, "spotlight->color", P_T_COLOR));
	return (P_SUCCESS);
}

int	parse_spot_light(t_context *context)
{
	t_spot_light	*sl;
	t_list			*node;

	sl = ft_calloc(1, sizeof(t_spot_light));
	node = ft_lstnew(LIG_SPOT, sl);
	if (node == NULL || sl == NULL)
		return (parse_spot_light_fail(node, sl, P_ERR_SYSCALL));
	ft_lstadd_front(&context->scene->light_list, node);
	if (parse_spot_light_part(context, sl))
		return (P_ERR_SYNTEX);
	sl->color = v3_rescale(sl->color, \
							get_named_range(RNG_COLOR), \
							get_named_range(RNG_RATIO));
	return (parse_endl(context));
}
