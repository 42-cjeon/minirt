/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_complex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:12:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/02 12:55:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector3.h"

double	v3_length(t_vector3 v)
{
	return (
		sqrt (
			v.x * v.x
			+ v.y * v.y
			+ v.z * v.z
		)
	);
}

double	v3_dot(t_vector3 u, t_vector3 v)
{
	return (
		u.x * v.x
		+ u.y * v.y
		+ u.z * v.z
	);
}

t_vector3	v3_cross(t_vector3 u, t_vector3 v)
{
	t_vector3	c;

	c.x = u.y * v.z - u.z * v.y;
	c.y = u.z * v.x - u.x * v.z;
	c.z = u.x * v.y - u.y * v.x;
	return (c);
}

t_vector3	v3_reflect(t_vector3 ray, t_vector3 axis)
{
	return (
		v3_sub (
			v3_mul_scalar(axis, 2.0 * v3_dot(ray, axis)), \
			ray
		)
	);
}

t_vector3	v3_transform(t_vector3 v, const t_tmat m)
{
	t_vector3	new;

	new.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0];
	new.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1];
	new.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2];
	return (new);
}
