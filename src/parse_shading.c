/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:53:39 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 01:04:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_window.h"
#include "parser.h"
#include "utils.h"
#include "texture.h"

int add_texture(t_context *context, int type, char *name)
{
	t_mlx_image	*img;
	t_list		*node;

	img = load_xpm_image(context->window, name);
	node = ft_lstnew(type, img);
	if (node == NULL || img == NULL)
	{
		free(node);
		free(img);
		return (P_ERR_SYSCALL);
	}
	ft_lstadd_front(&context->scene->texture_list, node);
	return (P_SUCCESS);
}

int	parse_texture(t_context *context, int type, char **pstr)
{
	int			start;

	start = context->col;
	while (*context_peek(context) && !(ft_isspace(*context_peek(context))))
		context->col++;
	if (context->col == start)
		return (P_ERR_SYNTEX);
	*pstr = ft_substr(context->line, start, context->col - start);
	if (*pstr == NULL)
		return (P_ERR_SYSCALL);
	return (add_texture(context, type, *pstr));
}

int	parse_surface(t_context *context, t_shading *shading)
{
	int	result;

	if (streq_part(context_peek(context), "color:"))
	{
		shading->surf_type = SURF_COLOR;
		if (parse_vector3(context_pop(context, 6), get_named_range(RNG_COLOR), &shading->surf.albedo))
			return (throw_error(context, "shading->albedo", P_T_COLOR));
		shading->surf.albedo = v3_rescale(shading->surf.albedo, get_named_range(RNG_COLOR), get_named_range(RNG_RATIO));
	}
	else if (streq_part(context_peek(context), "cb"))
	{
		shading->surf_type = SURF_CB;
		context_pop(context, 2);
	}
	else if (streq_part(context_peek(context), "texture:"))
	{
		shading->surf_type = SURF_TEXTURE;
		result = parse_texture(context_pop(context, 8), TXT_TEXTURE, &shading->surf.texture_name);
		if (result == P_ERR_SYSCALL)
			return (P_ERR_SYSCALL);
		else if (result == P_ERR_SYNTEX)
			return (throw_error(context, "shading->texture", P_T_STR));
	}
	else
		return (throw_error(context, "surface(color|cb|texture)", P_T_STR));
	return (P_SUCCESS);
}

int parse_shading(t_context *context, t_shading *shading)
{
	int	failure;

	if (parse_double(ignore_space(context), get_named_range(RNG_POS), &shading->ks))
		return (throw_error(context, "shading->ks", P_T_POS));
	if (parse_int(ignore_space(context), get_named_range(RNG_POS), &shading->kss))
		return (throw_error(context, "shading->kss", P_T_POS));
	failure = parse_surface(ignore_space(context), shading);
	if (failure)
		return (failure);
	if (shading->surf_type != SURF_CB && streq_part(context_peek(context), "nm:"))
	{
		failure = parse_texture(context, TXT_NMAP, &shading->nmap_name);
		if (failure)
			return (failure);
	}
	return (P_SUCCESS);
}