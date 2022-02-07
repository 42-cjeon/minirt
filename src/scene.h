/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:07:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 14:03:41 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "objects.h"
# include "camera.h"
# include "light.h"
# include "libft.h"

typedef struct s_scene
{
	t_camera		camera;
	t_list			*obj_list;	
	t_list			*light_list;
	t_global_light	gl;
}	t_scene;

#endif