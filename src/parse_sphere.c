/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:22:12 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_sphere_fail(t_sphere *sp)
{
	free(sp);
	return (1);
}

static char	*parse_sphere_part(char *line, t_sphere *sp)
{
	line = parse_vector3(ignore_space(line), get_named_range(RNG_INF), \
							&sp->origin);
	if (line == NULL)
		return (NULL);
	line = parse_double(ignore_space(line), get_named_range(RNG_INF), \
							&sp->radius);
	if (line == NULL)
		return (NULL);
	line = parse_vector3(ignore_space(line), get_named_range(RNG_COLOR), \
							&sp->shading.albedo);
	if (line == NULL)
		return (NULL);
	return (line);
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sp;
	t_list		*node;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (2);
	line = parse_sphere_part(line, sp);
	if (line == NULL)
		return (parse_sphere_fail(sp));
	node = ft_lstnew(OBJ_SPHERE, sp);
	if (node == NULL)
	{
		free(sp);
		return (2);
	}
	ft_lstadd_front(&scene->obj_list, node);
	sp->shading.albedo = v3_rescale(sp->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_ZERO_ONE));
	return (parse_endl(line));
}
