/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:00:28 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_cylinder_fail(t_cylinder *cy)
{
	free(cy);
	return (1);
}

char	*parse_cylinder_parts(char *line, t_cylinder *cy)
{
	line = parse_vector3(ignore_space(line), get_named_range(RNG_INF), \
							&cy->origin);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_UNITV), \
							&cy->dir);
	if (line == NULL)
		return (NULL);
	line = parse_double(ignore_space(line), get_named_range(RNG_INF), \
							&cy->radius);
	if (line == NULL)
		return (NULL);
	line = parse_double(ignore_space(line), get_named_range(RNG_INF), \
							&cy->height);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_COLOR), \
							&cy->shading.albedo);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;
	t_list		*node;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (2);
	line = parse_cylinder_parts(line, cy);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	node = ft_lstnew(OBJ_CYLINDER, cy);
	if (node == NULL)
	{
		free(cy);
		return (2);
	}
	cy->shading.albedo = v3_rescale(cy->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_ZERO_ONE));
	ft_lstadd_front(&scene->obj_list, node);
	return (parse_endl(line));
}
