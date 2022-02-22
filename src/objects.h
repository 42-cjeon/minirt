/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:46:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/21 01:42:05 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector3.h"
# include "ray.h"
# include "libft.h"
# include "scene.h"
# include "light.h"

enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
};

typedef struct s_sphere
{
	t_vector3	origin;
	double		radius;
	t_phong		phong;
}	t_sphere;

typedef struct s_plane
{
	t_vector3	origin;
	t_vector3	normal;	
	t_phong		phong;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3	origin;
	t_vector3	dir;
	double		height;
	double		diameter;
	t_phong		phong;
}	t_cylinder;

int	hit_object(t_ray ray, t_list *list, t_hit_record *record);
int	hit_plane(t_ray ray, t_plane *plane, t_hit_record *record);
int	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit_record *record);
int	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *record);

#endif