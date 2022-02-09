/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:46:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 00:49:40 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector3.h"

enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
};

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

int	hit_object(t_ray ray, t_list *list, t_hit_record *record);

#endif