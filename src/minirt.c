/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 14:44:22 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minirt.h"
#include "mlx.h"
#include "mlx_event.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_window	window;
	t_scene		scene;

	if (argc != 2)
	{
		ft_puterror("usage: ./minirt filename.rt");
		return (RT_ERR_ARG);
	}
	if (get_minirt_window(&window) || register_handler(&window))
		return (RT_ERR_MLX);
	if (parse_scene(argv[1], &scene, &window))
		return (RT_ERR_FILE);
	if (draw_scene(&window, &scene))
		return (RT_ERR_SYSCALL);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
							window.image.img_ptr, 0, 0);
	mlx_loop(window.mlx_ptr);
	return (RT_SUCCESS);
}
