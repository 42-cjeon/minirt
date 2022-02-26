/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:46:36 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/26 20:59:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "scene.h"

void		handle_nmap(t_scene	*scene, t_hit_record *record);
uint32_t	get_texture_pixel(t_mlx_image *img, double u, double v);
t_mlx_image	*search_texture(t_scene *scene, char *name, int type);
t_mlx_image	*load_xpm_image(t_window *window, char *name);
t_vector3	get_surf_color(t_scene *scene, t_hit_record *record);

#endif