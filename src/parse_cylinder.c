/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:12:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_cylinder_fail(t_cylinder *cy)
{
	free(cy);
	return (P_ERR_SYNTEX);
}

static int	parse_cylinder_parts(t_context *context, t_cylinder *cy)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&cy->origin))
		return (throw_error(context, "cylinder->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_UNITV), \
						&cy->dir))
		return (throw_error(context, "cylinder->dir", P_T_UNITV));
	if (parse_double(ignore_space(context), get_named_range(RNG_INF), \
						&cy->radius))
		return (throw_error(context, "cylinder->radius", P_T_DOUBLE));
	if (parse_double(ignore_space(context), get_named_range(RNG_INF), \
						&cy->height))
		return (throw_error(context, "cylinder->height", P_T_DOUBLE));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&cy->shading.albedo))
		return (throw_error(context, "cylinder->color", P_T_COLOR));
	return (P_SUCCESS);
}

int	parse_cylinder(t_context *context, t_scene *scene)
{
	t_cylinder	*cy;
	t_list		*node;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (P_ERR_SYSCALL);
	if (parse_cylinder_parts(context, cy))
		return (parse_cylinder_fail(cy));
	node = ft_lstnew(OBJ_CYLINDER, cy);
	if (node == NULL)
	{
		free(cy);
		return (P_ERR_SYSCALL);
	}
	cy->shading.albedo = v3_rescale(cy->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_RATIO));
	ft_lstadd_front(&scene->obj_list, node);
	return (parse_endl(context));
}
