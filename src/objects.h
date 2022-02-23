/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:46:57 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 22:46:56 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector3.h"
# include "libft.h"

typedef struct s_quadratic_eq
{
	double	a;
	double	hb;
	double	c;
	double	d;
}	t_quadratic_eq;

enum e_root_type
{
	ROOT_ALPHA,
	ROOT_BETA
};

enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
};

typedef struct s_shading
{
	t_color3	albedo;
}	t_shading;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}	t_ray;

typedef struct s_hit_record
{
	t_vector3	normal;
	t_vector3	point;
	t_shading	shading;
	double		distence;
}	t_hit_record;

typedef struct s_sphere
{
	t_vector3	origin;
	double		radius;
	t_shading	shading;
}	t_sphere;

typedef struct s_plane
{
	t_vector3	origin;
	t_vector3	dir;	
	t_shading	shading;
}	t_plane;

typedef struct s_cylinder
{
	t_vector3	origin;
	t_vector3	dir;
	double		height;
	double		radius;
	t_shading	shading;
}	t_cylinder;

int		quad_has_root(t_quadratic_eq *eq);
double	quad_get_root(const t_quadratic_eq *eq, enum e_root_type type);
int		hit_object(const t_ray *ray, t_list *list, t_hit_record *record);
int		hit_plane(const t_ray *ray, t_plane *plane, t_hit_record *record);
int		hit_sphere(const t_ray *ray, t_sphere *sphere, t_hit_record *record);
int		hit_cylinder(const t_ray *ray, t_cylinder *cylinder, \
						t_hit_record *record);
#endif