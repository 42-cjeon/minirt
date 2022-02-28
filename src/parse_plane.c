/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 15:00:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_plane_fail(t_list *node, t_plane *pl, int result)
{
	free(node);
	free(pl);
	return (result);
}

static int	parse_plane_part(t_context *context, t_plane *pl)
{
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_INF), &pl->origin))
		return (throw_error(context, "plane->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_UNITV), &pl->dir) \
		|| v3_equal(pl->dir, get_vector3(0, 0, 0)))
		return (throw_error(context, "plane->dir", P_T_UNITV));
	pl->dir = v3_to_unit(pl->dir);
	return (P_SUCCESS);
}

int	parse_plane(t_context *context)
{
	t_plane	*pl;
	t_list	*node;
	int		failure;

	pl = ft_calloc(1, sizeof(t_plane));
	node = ft_lstnew(OBJ_PLANE, pl);
	if (node == NULL || pl == NULL)
		return (parse_plane_fail(node, pl, P_ERR_SYSCALL));
	ft_lstadd_front(&context->scene->obj_list, node);
	if (parse_plane_part(context, pl))
		return (P_ERR_SYNTEX);
	failure = parse_shading(context, &pl->shading);
	if (failure)
		return (failure);
	return (parse_endl(context));
}
