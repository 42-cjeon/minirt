/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:20:06 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 19:00:41 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>
# include "vector3.h"

/*
# define WINDOW_W (1920.0)
# define WINDOW_H (WINDOW_W / ASPECT_RATIO)
# define FOV_W (M_PI * (2.0 / 3.0))
# define FOW_H (FOV_W / ASPECT_RATIO)
*/

typedef struct s_camera
{
	t_point3	origin;
	t_vector3	dir;
	double		fov_w;
	double		fov_h;
}	t_camera;

#endif