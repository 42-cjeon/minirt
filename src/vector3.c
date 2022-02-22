/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:47:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 01:57:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector3.h"

t_vector3	v3_add(t_vector3 u, t_vector3 v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	return (u);
}

t_vector3	v3_add_scaler(t_vector3 v, double k)
{
	v.x += k;
	v.y += k;
	v.z += k;
	return (v);
}

t_vector3	v3_sub(t_vector3 u, t_vector3 v)
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
	return (u);
}

t_vector3	v3_sub_scaler(t_vector3 v, double k)
{
	v.x -= k;
	v.y -= k;
	v.z -= k;
	return (v);
}

t_vector3	v3_mul(t_vector3 u, t_vector3 v)
{
	u.x *= v.x;
	u.y *= v.y;
	u.z *= v.z;
	return (u);
}

t_vector3	v3_mul_scaler(t_vector3 v, double k)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
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

t_vector3	v3_minmax_trunc(t_vector3 v, double min, double max)
{
	if (v.x < min)
		v.x = min;
	else if (max < v.x)
		v.x = max;
	if (v.y < min)
		v.y = min;
	else if (max < v.y)
		v.y = max;
	if (v.z < min)
		v.z = min;
	else if (max < v.z)
		v.z = max;
	return (v);
}

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

/*
	ray direction must face to axis
*/
t_vector3	v3_reflect(t_vector3 ray, t_vector3 axis)
{
	return (
		v3_sub (
			v3_mul_scaler(axis, 2.0 * v3_dot(ray, axis)), \
			ray
		)
	);
}

t_vector3	v3_rotate(t_vector3 dir, t_vector3 ea)
{
	t_vector3		new_dir;
	const double	r[3][3] = \
	{
		{
			cos(ea.y) * cos(ea.z), \
			sin(ea.x) * sin(ea.y) * cos(ea.z) - cos(ea.x) * sin(ea.z), \
			sin(ea.x) * sin(ea.z) + cos(ea.x) * sin(ea.y) * cos(ea.z)
		},
		{
			cos(ea.y) * sin(ea.z), \
			cos(ea.x) * cos(ea.z) + sin(ea.x) * sin(ea.y) * sin(ea.z), \
			cos(ea.x) * sin(ea.y) * sin(ea.z) - sin(ea.x) * cos(ea.z)
		},
		{
			-sin(ea.y), \
			sin(ea.x) * cos(ea.y), \
			cos(ea.x) * cos(ea.y)
		}
	};

	new_dir.x = r[0][0] * dir.x + r[0][1] * dir.y + r[0][2] * dir.z;
	new_dir.y = r[1][0] * dir.x + r[1][1] * dir.y + r[1][2] * dir.z;
	new_dir.z = r[2][0] * dir.x + r[2][1] * dir.y + r[2][2] * dir.z;
	return (new_dir);
}

t_range	get_range(enum e_range_type type, double min, double max)
{
	t_range	range;

	range.closed = type;
	range.min = min;
	range.max = max;
	return (range);
}

int is_in_range(double d, t_range range)
{
	if (range.closed)
	{
		if (range.min <= d && d <= range.max)
			return (1);
		return (0);
	}
	else
	{
		if (range.min < d && d < range.max)
			return (1);
		return (0);
	}
}

double	scaler_rescale(double k, t_range from, t_range to)
{
	double	std;
	
	std = (k - from.min) / (from.max - from.min);
	return (std * (to.max - to.min) + to.min);
}

t_vector3	v3_rescale(t_vector3 v, t_range from, t_range to)
{
	v.x = scaler_rescale(v.x, from, to);
	v.y = scaler_rescale(v.y, from, to);
	v.z = scaler_rescale(v.z, from, to);
	return (v);
}
