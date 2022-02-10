/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:36:48 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/10 16:15:40 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "mlx.h"
#include "ft_window.h"
#include "libft.h"
#include "utils.h"

#include <stdio.h>
static int	is_supported_platform(t_mlx_image *img)
{
	return (
		img->bpp == sizeof(uint32_t) * 8
		&& img->endian == MLX_LITTLE_ENDIAN
	);
}

static int	window_init_fail(t_window *window)
{
	ft_puterror("miniRT: failed to initialize mlx");
	if (!window->mlx_ptr)
		return (1);
	if (window->win_ptr)
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	else
		return (1);
	if (window->image.img_ptr)
		mlx_destroy_image(window->mlx_ptr, window->image.img_ptr);
	return (1);
}

int	get_minirt_window(t_window *window)
{
	ft_memset(window, 0, sizeof(window));
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		return (window_init_fail(window));
	window->win_ptr = mlx_new_window(window->mlx_ptr, WINDOW_WIDTH, \
										WINDOW_HEIGHT, "miniRT");
	if (!window->win_ptr)
		return (window_init_fail(window));
	window->image.img_ptr = mlx_new_image(window->mlx_ptr, WINDOW_WIDTH, \
											WINDOW_HEIGHT);
	if (!window->image.img_ptr)
		return (window_init_fail(window));
	window->image.data = (uint32_t *)mlx_get_data_addr(window->image.img_ptr, \
											&window->image.bpp, \
											&window->image.line_size, \
											&window->image.endian);
	if (!window->image.data || !is_supported_platform(&window->image))
		return (window_init_fail(window));
	return (0);
}
