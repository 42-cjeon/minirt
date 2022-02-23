/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 01:28:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "minirt.h"
#include "mlx.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

#define X11_BUTTONPRESS 4
#define X11_KEYPRESS 2
#define X11_DESTROYNOTIFY 17

#define X11_NOMASK (0L)
#define X11_KEYPRESS_MASK (1L)
#define X11_BUTTONPRESS_MASK (4L)

#define KB_ESC 53

int handle_keyevent(int code, void *arg)
{
	(void)arg;
	if (code == KB_ESC)
		exit(0);
	return (0);
}

int exit_helper(void *arg)
{
	(void)arg;
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_window	window;
	t_scene		scene;

	if (argc != 2)
	{
		ft_puterror("usage: ./minirt filename.rt");
		return (RT_ERR_ARG);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_perror("miniRT");
		return (RT_ERR_FILE);
	}
	if (parse_scene(fd, &scene))
		return (RT_ERR_FILE);
	if (get_minirt_window(&window))
		return (RT_ERR_MLX);
	if (draw_scene(&window, &scene))
		return (RT_ERR_SYSCALL);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
							window.image.img_ptr, 0, 0);
	mlx_hook(window.win_ptr, X11_KEYPRESS, X11_KEYPRESS_MASK, handle_keyevent, NULL);
	mlx_hook(window.win_ptr, X11_DESTROYNOTIFY, X11_NOMASK, exit_helper, NULL);
	mlx_loop(window.mlx_ptr);
	return (RT_SUCCESS);
}
