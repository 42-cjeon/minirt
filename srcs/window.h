/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:41:03 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/06 19:41:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_h

# include <math.h>

# define ASPECT_RATIO (16.0 / 9.0)
# define WINDOW_W (1920.0)
# define WINDOW_H (WINDOW_W / ASPECT_RATIO)
# define FOV_W (M_PI * (2.0 / 3.0))
# define FOW_H (FOV_W / ASPECT_RATIO)

#endif