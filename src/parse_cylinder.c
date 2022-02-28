/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 14:56:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_cylinder_fail(t_list *node, t_cylinder *cy, int result)
{
	free(cy);
	free(node);
	return (result);
}

static int	parse_cylinder_parts(t_context *context, t_cylinder *cy)
{
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_INF), &cy->origin))
		return (throw_error(context, "cylinder->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_UNITV), &cy->dir) \
		|| v3_equal(cy->dir, get_vector3(0, 0, 0)))
		return (throw_error(context, "cylinder->dir", P_T_UNITV));
	cy->dir = v3_to_unit(cy->dir);
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_INF), &cy->radius))
		return (throw_error(context, "cylinder->radius", P_T_DOUBLE));
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_INF), &cy->height))
		return (throw_error(context, "cylinder->height", P_T_DOUBLE));
	return (P_SUCCESS);
}

int	parse_cylinder(t_context *context)
{
	t_cylinder	*cy;
	t_list		*node;
	int			failure;

	cy = ft_calloc(1, sizeof(t_cylinder));
	node = ft_lstnew(OBJ_CYLINDER, cy);
	if (cy == NULL || node == NULL)
		return (parse_cylinder_fail(node, cy, P_ERR_SYSCALL));
	ft_lstadd_front(&context->scene->obj_list, node);
	if (parse_cylinder_parts(context, cy))
		return (P_ERR_SYNTEX);
	failure = parse_shading(context, &cy->shading);
	if (failure)
		return (failure);
	return (parse_endl(context));
}
