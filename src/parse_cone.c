/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:57:14 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/01 14:29:28 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_cone_fail(t_list *node, t_cone *cn, int result)
{
	free(cn);
	free(node);
	return (result);
}

static int	parse_cone_parts(t_context *context, t_cone *cn)
{
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_INF), &cn->origin))
		return (throw_error(context, "cone->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_UNITV), &cn->dir) \
		|| v3_equal(cn->dir, get_vector3(0, 0, 0)))
		return (throw_error(context, "cone->dir", P_T_UNITV));
	cn->dir = v3_to_unit(cn->dir);
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_INF), &cn->radius))
		return (throw_error(context, "cone->radius", P_T_DOUBLE));
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_INF), &cn->height))
		return (throw_error(context, "cone->height", P_T_DOUBLE));
	return (P_SUCCESS);
}

int	parse_cone(t_context *context)
{
	t_cone	*cn;
	t_list	*node;
	int		failure;

	cn = ft_calloc(1, sizeof(t_cone));
	node = ft_lstnew(OBJ_CONE, cn);
	if (cn == NULL || node == NULL)
		return (parse_cone_fail(node, cn, P_ERR_SYSCALL));
	ft_lstadd_front(&context->scene->obj_list, node);
	if (parse_cone_parts(context, cn))
		return (P_ERR_SYNTEX);
	failure = parse_shading(context, &cn->shading);
	if (failure)
		return (failure);
	return (parse_endl(context));
}
