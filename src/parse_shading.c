/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:53:39 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 15:01:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_window.h"
#include "parser.h"
#include "utils.h"
#include "texture.h"

int	add_texture(t_context *context, int type, char *name)
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
	int	start;

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

int	parse_shading(t_context *context, t_shading *shading)
{
	int	failure;

	if (parse_double(ignore_space(context), \
		get_named_range(RNG_POS), &shading->ks))
		return (throw_error(context, "shading->ks", P_T_POS));
	if (parse_int(ignore_space(context), \
		get_named_range(RNG_POS), &shading->kss))
		return (throw_error(context, "shading->kss", P_T_POS));
	failure = parse_surface(ignore_space(context), shading);
	if (failure)
		return (failure);
	ignore_space(context);
	if (shading->surf_type != SURF_CB \
		&& streq_part(context_peek(context), "nm:"))
	{
		failure = parse_texture(context_pop(context, 3), \
								TXT_NMAP, &shading->nmap_name);
		if (failure == P_ERR_SYNTEX)
			return (throw_error(context, "shading->nmap", P_T_STR));
		if (failure)
			return (failure);
	}
	return (P_SUCCESS);
}
