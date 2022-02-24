/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:13:49 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_plane_fail(t_plane *pl)
{
	free(pl);
	return (P_ERR_SYNTEX);
}

static int	parse_plane_part(t_context *context, t_plane *pl)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&pl->origin))
		return (throw_error(context, "plane->origin", P_T_POINT));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_UNITV), \
						&pl->dir))
		return (throw_error(context, "plane->dir", P_T_UNITV));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&pl->shading.albedo))
		return (throw_error(context, "plane->color", P_T_COLOR));
	return (P_SUCCESS);
}

int	parse_plane(t_context *context, t_scene *scene)
{
	t_plane	*pl;
	t_list	*node;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (P_ERR_SYSCALL);
	if (parse_plane_part(context, pl))
		return (parse_plane_fail(pl));
	node = ft_lstnew(OBJ_PLANE, pl);
	if (node == NULL)
	{
		free(pl);
		return (P_ERR_SYSCALL);
	}
	ft_lstadd_front(&scene->obj_list, node);
	pl->shading.albedo = v3_rescale(pl->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_RATIO));
	return (parse_endl(context));
}
