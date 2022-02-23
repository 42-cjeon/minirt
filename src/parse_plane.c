/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:21:46 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_plane_fail(t_plane *pl)
{
	free(pl);
	return (1);
}

static char	*parse_plane_part(char *line, t_plane *pl)
{
	line = parse_vector3(ignore_space(line), get_named_range(RNG_INF), \
							&pl->origin);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_UNITV), \
							&pl->dir);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_COLOR), \
							&pl->shading.albedo);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	*pl;
	t_list	*node;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (2);
	line = parse_plane_part(line, pl);
	if (line == NULL)
		return (parse_plane_fail(pl));
	node = ft_lstnew(OBJ_PLANE, pl);
	if (node == NULL)
	{
		free(pl);
		return (2);
	}
	ft_lstadd_front(&scene->obj_list, node);
	pl->shading.albedo = v3_rescale(pl->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_ZERO_ONE));
	return (parse_endl(line));
}
