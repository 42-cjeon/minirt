/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:16:31 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 15:22:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector3.h"
# include "libft.h"
# include "light.h"

typedef struct s_ray
{
	t_point3	origin;
	t_vector3	dir;
}	t_ray;

typedef struct s_hit_record
{
	t_vector3	normal;
	t_point3	point;
	t_phong		phong;
	void		*object;
	double		distence;
}	t_hit_record;

#endif