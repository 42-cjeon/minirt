/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:41:03 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 20:36:21 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WINDOW_H
# define FT_WINDOW_H

# include <stdint.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_mlx_image
{
	char		*name;
	void		*img_ptr;
	uint32_t	*data;
	int			bpp;
	int			height;
	int			width;
	int			line_size;
	int			endian;
}	t_mlx_image;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_image	image;
}	t_window;

int	get_minirt_window(t_window *window);

#endif