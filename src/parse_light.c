/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:48 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:21:31 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

int	parse_ambient(char *line, t_scene *scene)
{
	line = parse_double(ignore_space(line), get_named_range(RNG_ZERO_ONE), \
							&scene->ambient.ratio);
	if (!line)
		return (1);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_COLOR), \
							&scene->ambient.color);
	if (!line)
		return (1);
	scene->ambient.color = v3_rescale(scene->ambient.color, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_ZERO_ONE));
	return (parse_endl(line));
}

static int	parse_point_light_fail(t_point_light *pl)
{
	free(pl);
	return (1);
}

static char	*parse_point_light_part(char *line, t_point_light *pl)
{
	line = parse_vector3(ignore_space(line), get_named_range(RNG_INF), \
							&pl->origin);
	if (line == NULL)
		return (NULL);
	line = parse_double(ignore_space(line), get_named_range(RNG_ZERO_ONE), \
							&pl->ratio);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_COLOR), \
							&pl->color);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	parse_point_light(char *line, t_scene *scene)
{
	t_point_light	*pl;
	t_list			*node;

	pl = malloc(sizeof(t_point_light));
	if (pl == NULL)
		return (2);
	line = parse_point_light_part(line, pl);
	if (line == NULL)
		return (parse_point_light_fail(pl));
	node = ft_lstnew(LIG_POINT, pl);
	if (node == NULL)
	{
		free(pl);
		return (2);
	}
	pl->color = v3_rescale(pl->color, \
							get_named_range(RNG_COLOR), \
							get_named_range(RNG_ZERO_ONE));
	ft_lstadd_front(&scene->light_list, node);
	return (parse_endl(line));
}
