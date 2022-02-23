/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:47:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:24:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

int	v3_equal(t_vector3 u, t_vector3 v)
{
	return (
		u.x == v.x
		&& u.y == v.y
		&& u.z == v.z
	);
}

t_vector3	get_vector3(double x, double y, double z)
{
	t_vector3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector3	v3_to_unit(t_vector3 v)
{
	double	length;

	length = v3_length(v);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return (v);
}

t_vector3	v3_rescale(t_vector3 v, t_range from, t_range to)
{
	v.x = scaler_rescale(v.x, from, to);
	v.y = scaler_rescale(v.y, from, to);
	v.z = scaler_rescale(v.z, from, to);
	return (v);
}
