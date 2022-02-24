/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:14:01 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_sphere_fail(t_sphere *sp)
{
	free(sp);
	return (P_ERR_SYNTEX);
}

static int	parse_sphere_part(t_context *context, t_sphere *sp)
{
	if (parse_vector3(ignore_space(context), get_named_range(RNG_INF), \
						&sp->origin))
		return (throw_error(context, "sphere->origin", P_T_POINT));
	if (parse_double(ignore_space(context), get_named_range(RNG_INF), \
						&sp->radius))
		return (throw_error(context, "sphere->radius", P_T_DOUBLE));
	if (parse_vector3(ignore_space(context), get_named_range(RNG_COLOR), \
						&sp->shading.albedo))
		return (throw_error(context, "sphere->color", P_T_COLOR));
	return (P_SUCCESS);
}

int	parse_sphere(t_context *context, t_scene *scene)
{
	t_sphere	*sp;
	t_list		*node;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (P_ERR_SYSCALL);
	if (parse_sphere_part(context, sp))
		return (parse_sphere_fail(sp));
	node = ft_lstnew(OBJ_SPHERE, sp);
	if (node == NULL)
	{
		free(sp);
		return (P_ERR_SYSCALL);
	}
	ft_lstadd_front(&scene->obj_list, node);
	sp->shading.albedo = v3_rescale(sp->shading.albedo, \
										get_named_range(RNG_COLOR), \
										get_named_range(RNG_RATIO));
	return (parse_endl(context));
}
