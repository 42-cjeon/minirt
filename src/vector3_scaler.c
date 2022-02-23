/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_scaler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:12:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 23:23:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	v3_add_scaler(t_vector3 v, double k)
{
	v.x += k;
	v.y += k;
	v.z += k;
	return (v);
}

t_vector3	v3_sub_scaler(t_vector3 v, double k)
{
	v.x -= k;
	v.y -= k;
	v.z -= k;
	return (v);
}

t_vector3	v3_mul_scaler(t_vector3 v, double k)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	return (v);
}
