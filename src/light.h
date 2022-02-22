/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:09:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/21 02:36:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector3.h"

enum e_light_type
{
	LIG_SPOT,
	LIG_POINT
};

typedef struct s_phong
{
	t_color3	albedo;
}	t_phong;

typedef struct s_point_light
{
	t_point3	origin;
	t_color3	color;
	double		ratio;
}	t_point_light;

typedef struct s_spot_light
{
	t_point3	origin;
	t_color3	color;
	t_vector3	dir;
	double		theta;
}	t_spot_light;

typedef struct s_glogal_light
{
	t_color3	ambient;
	double		ratio;
}	t_global_light;

#endif