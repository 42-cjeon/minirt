/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:41:18 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 02:02:31 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

enum e_bool
{
	FALSE = 0,
	TRUE = 1
};

struct s_vector3
{
	double	x;
	double	y;
	double	z;
};

enum e_range_type
{
	RANGE_CLOSED = 1,
	RANGE_OPEN = 0
};

typedef struct s_range
{
	enum e_range_type	closed;
	double				min;
	double				max;
}							t_range;

typedef struct s_vector3	t_vector3;
typedef struct s_vector3	t_color3;

t_vector3	v3_add(t_vector3 u, t_vector3 v);
t_vector3	v3_add_scaler(t_vector3 v, double k);
t_vector3	v3_sub(t_vector3 u, t_vector3 v);
t_vector3	v3_sub_scaler(t_vector3 v, double k);
t_vector3	v3_mul(t_vector3 u, t_vector3 v);
t_vector3	v3_mul_scaler(t_vector3 v, double k);
t_vector3	v3_to_unit(t_vector3 v);
t_vector3	v3_cross(t_vector3 u, t_vector3 v);
double		v3_length(t_vector3 v);
double		v3_dot(t_vector3 u, t_vector3 v);
t_vector3	v3_reflect(t_vector3 ray, t_vector3 axis);
t_vector3	v3_rotate(t_vector3 dir, t_vector3 ea);
t_range		get_range(enum e_range_type type, double min, double max);
int			is_in_range(double d, t_range range);
t_vector3	v3_rescale(t_vector3 v, t_range from, t_range to);
double		scaler_rescale(double k, t_range from, t_range to);

#endif