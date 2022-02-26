/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:31:38 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/26 17:51:42 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "minirt.h"
#include "mlx.h"
#include "mlx_event.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

t_mlx_image texture;
t_mlx_image nmap;

void read_texture(char *name, t_window *window, t_mlx_image *img)
{
	img->img_ptr = mlx_xpm_file_to_image(window->mlx_ptr, name, &img->width, &img->height);
	if (img->img_ptr == NULL)
	{
		ft_puterror("miniRT: cannot open texture file");
		exit(123);
	}
	printf("IMG W: %d, H: %d\n", img->width, img->height);
	img->data = (uint32_t *)mlx_get_data_addr(img->img_ptr, \
											&img->bpp, \
											&img->line_size, \
											&img->endian);
	if (img->data == NULL)
	{
		ft_puterror("miniRT: invalid texture file");
		exit(123);
	}
}

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
	read_texture("wall.xpm", &window, &texture);
	read_texture("wall_nmap.xpm", &window, &nmap);
	if (draw_scene(&window, &scene))
		return (RT_ERR_SYSCALL);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
							window.image.img_ptr, 0, 0);
	mlx_loop(window.mlx_ptr);
	return (RT_SUCCESS);
}
