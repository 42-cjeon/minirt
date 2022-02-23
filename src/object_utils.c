/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:22:14 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 22:52:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "objects.h"

int	quad_has_root(t_quadratic_eq *eq)
{
	eq->d = eq->hb * eq->hb - eq->a * eq->c;
	if (0 <= eq->d)
		return (TRUE);
	return (FALSE);
}

double	quad_get_root(const t_quadratic_eq *eq, enum e_root_type type)
{
	if (type == ROOT_ALPHA)
		return ((-eq->hb - sqrt(eq->d)) / eq->a);
	if (type == ROOT_BETA)
		return ((-eq->hb + sqrt(eq->d)) / eq->a);
	return (NAN);
}
