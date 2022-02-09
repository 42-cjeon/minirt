/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 15:32:37 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "ft_window.h"
# include "camera.h"
# include "libft.h"

typedef struct s_scene
{
	t_camera		camera;
	t_list			*obj_list;	
	t_list			*light_list;
	t_global_light	gl;
}	t_scene;

int			draw_scene(t_window *window, t_scene *scene);
t_color3	calc_color(t_scene *scene, t_hit_record *record);
t_color3	get_object_color(t_scene *scene, t_hit_record *record);

#endif