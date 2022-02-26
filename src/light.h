/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:09:56 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 00:52:36 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector3.h"

enum e_light_type
{
	LIG_SPOT
};

typedef struct s_ambient
{
	t_color3	color;
	double		ratio;
}	t_ambient;

typedef struct s_spot_light
{
	t_vector3	origin;
	t_color3	color;
	t_vector3	dir;
	double		theta;
	double		ratio;
}	t_spot_light;

#endif