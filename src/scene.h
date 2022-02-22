/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 01:10:41 by cjeon            ###   ########.fr       */
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

int			draw_scene(t_window *window, t_scene *scene);
t_color3	calc_color(t_scene *scene, t_hit_record *record);
t_color3	get_object_color(t_scene *scene, t_hit_record *record);

#endif