/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:34:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 15:02:10 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"

static int	parse_sphere_fail(t_list *node, t_sphere *sp, int result)
{
	free(node);
	free(sp);
	return (result);
}

static int	parse_sphere_part(t_context *context, t_sphere *sp)
{
	if (parse_vector3(ignore_space(context), \
		get_named_range(RNG_INF), &sp->origin))
		return (throw_error(context, "sphere->origin", P_T_POINT));
	if (parse_double(ignore_space(context), \
		get_named_range(RNG_INF), &sp->radius))
		return (throw_error(context, "sphere->radius", P_T_DOUBLE));
	return (P_SUCCESS);
}

int	parse_sphere(t_context *context)
{
	t_sphere	*sp;
	t_list		*node;
	int			failure;

	sp = ft_calloc(1, sizeof(t_sphere));
	node = ft_lstnew(OBJ_SPHERE, sp);
	if (node == NULL || sp == NULL)
		return (parse_sphere_fail(node, sp, P_ERR_SYSCALL));
	ft_lstadd_front(&context->scene->obj_list, node);
	if (parse_sphere_part(context, sp))
		return (parse_sphere_fail(NULL, NULL, P_ERR_SYNTEX));
	failure = parse_shading(context, &sp->shading);
	if (failure)
		return (failure);
	return (parse_endl(context));
}
