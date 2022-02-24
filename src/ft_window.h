/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:41:03 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 20:38:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WINDOW_H
# define FT_WINDOW_H

# include <stdint.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_mlx_image
{
	void		*img_ptr;
	uint32_t	*data;
	int			bpp;
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