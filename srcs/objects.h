/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:46:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/06 19:35:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector3.h"

typedef struct s_phong
{
	t_color3	albedo;
}	t_phong;

typedef struct s_sphere
{
	t_vector3	origin;
	double		radius;
	t_phong		phong;
}	t_sphere;

#endif