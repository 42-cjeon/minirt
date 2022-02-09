/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:50:41 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 15:10:05 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "vector3.h"

t_color3	v3_lerp(t_color3 from, t_color3 to, double p)
{
	return (
		v3_add (
			v3_mul_scaler(from, 1.0 - p), \
			v3_mul_scaler(to, p)
		)
	);
}

uint32_t	v3_to_color(t_color3 v)
{
	uint32_t	color;

	color = 0;
	color |= (unsigned char)(0xFF * v.x);
	color <<= 8;
	color |= (unsigned char)(0xFF * v.y);
	color <<= 8;
	color |= (unsigned char)(0xFF * v.z);
	return (color);
}

void	trunc_color(t_vector3 *color)
{
	if (color->x < 0)
		color->x = 0;
	else if (1 < color->x)
		color->x = 1;
	if (color->y < 0)
		color->y = 0;
	else if (1 < color->y)
		color->y = 1;
	if (color->z < 0)
		color->z = 0;
	else if (1 < color->z)
		color->z = 1;
}