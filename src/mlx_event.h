/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:05:30 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:23:06 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EVENT_H
# define MLX_EVENT_H

# include "ft_window.h"

# define X11_BUTTONPRESS 4
# define X11_KEYPRESS 2
# define X11_DESTROYNOTIFY 17

# define X11_NOMASK (0L)
# define X11_KEYPRESS_MASK (1L)
# define X11_BUTTONPRESS_MASK (4L)

# define KB_ESC 53

int	register_handler(t_window *window);

#endif