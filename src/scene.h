/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 20:35:25 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ft_window.h"
# include "libft.h"
# include "light.h"
# include "objects.h"

# define CAMERA_NEAR (1e-5)
# define CAMERA_FAR (1e+5)
# define FOCAL_LEN 1.0

typedef struct s_camera
{
	t_vector3	origin;
	t_vector3	dir;
	double		fov_w;
	double		fov_h;
	double		focal_len;
	double		near;
	double		far;
}	t_camera;

typedef struct s_scene
{
	t_camera	camera;
	t_list		*obj_list;	
	t_list		*light_list;
	t_ambient	ambient;
}	t_scene;

int					draw_scene(t_window *window, t_scene *scene);
t_color3			calc_color(t_scene *scene, t_hit_record *record);
t_color3			get_object_color(t_scene *scene, t_hit_record *record);
t_vector3			get_global_ray_dir(const t_scene *scene, t_vector3 local);
t_vector3			get_local_ray_dir(const t_scene *scene, double y, double x);
t_ray				get_rotated_ray(const t_scene *scene, double y, double x);
t_transform_matrix	get_transform_matrix(const t_scene *scene, t_vector3 *xs, \
											t_vector3 *ys);
t_vector3			get_vup(t_vector3 dir);

#endif