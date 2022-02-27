/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:27:34 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 14:21:19 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "color.h"
#include "utils.h"

t_mlx_image	*load_xpm_image(t_window *window, char *name)
{
	t_mlx_image	*img;

	img = malloc(sizeof(t_mlx_image));
	if (img == NULL)
		return (NULL);
	img->img_ptr = mlx_xpm_file_to_image(window->mlx_ptr, name, &img->width, &img->height);
	if (img->img_ptr == NULL)
	{
		free(img);
		return (NULL);
	}
	img->data = (uint32_t *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_size, &img->endian);
	if (img->data == NULL)
	{
		free(img);
		return (NULL);
	}
	img->name = name;
	return (img);
}

t_mlx_image	*search_texture(t_scene *scene, char *name, int type)
{
	t_list		*txt;
	t_mlx_image	*img;
	txt = scene->texture_list;
	while (txt)
	{
		if (txt->type == type)
		{
			img = txt->content;
			if (streq(name, img->name))
				return (img);
		}
		txt = txt->next;
	}
	return (NULL);
}

uint32_t	get_texture_pixel(t_mlx_image *img, double u, double v)
{
	int	y;
	int	x;

	y = (int)(v * (img->height - 1));
	x = (int)(u * (img->width - 1));
	return (img->data[y * img->width + x]);
}

t_vector3	get_surf_color(t_scene *scene, t_hit_record *record)
{
	int			u;
	int			v;
	t_mlx_image	*img;

	if (record->shading.surf_type == SURF_COLOR)
		return (record->shading.surf.albedo);
	if (record->shading.surf_type == SURF_CB)
	{
		u = (int)(record->shading.u) % 2;
		v = (int)(record->shading.v) % 2;
		if ((u && v) || (!u && !v))
			return (get_vector3(0, 0, 0));
		else
			return (get_vector3(1, 1, 1));
	}
	if (record->shading.surf_type == SURF_TEXTURE)
	{
		img = search_texture(scene, record->shading.surf.texture_name, TXT_TEXTURE);
		return (color_to_v3(get_texture_pixel(img, record->shading.u, record->shading.v)));
	}
	else
		return (get_vector3(0.5, 0.5, 0.5));
}

void	handle_nmap(t_scene	*scene, t_hit_record *record)
{
	t_mlx_image	*nmap;
	t_vector3	nm;
	t_vector3	zerov;
	t_vector3	tn;
	t_vector3	bi;

	if (record->shading.nmap_name == NULL)
		return ;
	nmap = search_texture(scene, record->shading.nmap_name, TXT_NMAP);
	nm = v3_sub_scaler(v3_mul_scaler(color_to_v3(get_texture_pixel(nmap, record->shading.u, record->shading.v)), 2), 1);
	tn = v3_cross(get_vup(record->normal), record->normal);
	bi = v3_cross(record->normal, tn);
	zerov = get_vector3(0, 0, 0);
	record->normal = v3_transform(nm, get_transform_matrix(&tn, &bi, &record->normal, &zerov));
}