/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:04:59 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:35:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "mlx_event.h"
#include "utils.h"

int	handle_keyevent(int code, void *arg)
{
	(void)arg;
	if (code == KB_ESC)
		exit(0);
	return (0);
}

int	exit_helper(void *arg)
{
	(void)arg;
	exit(0);
	return (0);
}

int	register_handler(t_window *window)
{
	mlx_hook(window->win_ptr, X11_KEYPRESS, X11_KEYPRESS_MASK, \
					handle_keyevent, NULL);
	mlx_hook(window->win_ptr, X11_DESTROYNOTIFY, X11_NOMASK, \
					exit_helper, NULL);
	return (0);
}
