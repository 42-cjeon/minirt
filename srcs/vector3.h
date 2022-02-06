/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:41:18 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/06 22:48:40 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

struct s_vector3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vector3	t_vector3;
typedef struct s_vector3	t_color3;
typedef struct s_vector3	t_point3;

t_vector3	v3_add(t_vector3 u, t_vector3 v);
t_vector3	v3_add_scaler(t_vector3 v, double k);
t_vector3	v3_sub(t_vector3 u, t_vector3 v);
t_vector3	v3_sub_scaler(t_vector3 v, double k);
t_vector3	v3_mul(t_vector3 u, t_vector3 v);
t_vector3	v3_mul_scaler(t_vector3 v, double k);
t_vector3	v3_to_unit(t_vector3 v);
double		v3_length(t_vector3 v);
double		v3_dot(t_vector3 u, t_vector3 v);
t_vector3	v3_reflect(t_vector3 ray, t_vector3 axis);
t_vector3	v3_rotate(t_vector3 dir, t_vector3 ea);

#endif