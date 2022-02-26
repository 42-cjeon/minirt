/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/26 02:30:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "ft_window.h"
# include "libft.h"
# include "light.h"
# include "objects.h"

# define TEXTURE_IMAGE
//# define TEXTURE_CB
//# define SPECULA

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
}	t_camera;

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	int			window_height;
	int			window_width;
	double		kld;
	double		kldd;
	t_list		*obj_list;	
	t_list		*light_list;
}	t_scene;

int					draw_scene(t_window *window, t_scene *scene);
t_color3			calc_color(t_scene *scene, t_hit_record *record);
t_color3			get_object_color(t_scene *scene, t_hit_record *record);
t_vector3			get_global_ray_dir(t_scene *scene, t_vector3 local);
t_vector3			get_local_ray_dir(t_scene *scene, double y, double x);
t_ray				get_rotated_ray(t_scene *scene, double y, double x);
t_transform_matrix	get_transform_matrix(t_vector3 *xs, t_vector3 *ys, \
											t_vector3 *zs, t_vector3 *os);
t_vector3			get_vup(t_vector3 dir);

#endif