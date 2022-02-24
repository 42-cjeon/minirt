/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:15:51 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 15:39:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vector3.h"

t_range	get_named_range(enum e_range_name name)
{
	const static t_range	named_range[5] = {
		{RANGE_CLOSED, 0, 1},
		{RANGE_CLOSED, 0, 255},
		{RANGE_CLOSED, -1, 1},
		{RANGE_OPEN, 0, 180},
		{RANGE_OPEN, -INFINITY, INFINITY}
	};

	return (named_range[name]);
}

t_range	get_range(enum e_range_type type, double min, double max)
{
	t_range	range;

	range.closed = type;
	range.min = min;
	range.max = max;
	return (range);
}

int	is_in_range(double d, t_range range)
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
