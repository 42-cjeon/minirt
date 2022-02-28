/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_surface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:54:50 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 15:04:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

static int	parse_color_surface(t_context *context, t_shading *shading)
{
	shading->surf_type = SURF_COLOR;
	if (parse_vector3(context, \
		get_named_range(RNG_COLOR), &shading->surf.albedo))
		return (throw_error(context, "shading->albedo", P_T_COLOR));
	shading->surf.albedo = \
		v3_rescale(shading->surf.albedo, \
			get_named_range(RNG_COLOR), \
			get_named_range(RNG_RATIO));
	return (P_SUCCESS);
}

static int	parse_cb_surface(t_context *context, t_shading *shading)
{
	(void)context;
	shading->surf_type = SURF_CB;
	return (P_SUCCESS);
}

static int	parse_texture_surface(t_context *context, t_shading *shading)
{
	int	result;

	shading->surf_type = SURF_TEXTURE;
	result = parse_texture(context, TXT_TEXTURE, &shading->surf.texture_name);
	if (result == P_ERR_SYSCALL)
		return (P_ERR_SYSCALL);
	else if (result == P_ERR_SYNTEX)
		return (throw_error(context, "shading->texture", P_T_STR));
	return (P_SUCCESS);
}

int	parse_surface(t_context *context, t_shading *shading)
{
	if (streq_part(context_peek(context), "color:"))
		return (parse_color_surface(context_pop(context, 6), shading));
	else if (streq_part(context_peek(context), "cb"))
		return (parse_cb_surface(context_pop(context, 2), shading));
	else if (streq_part(context_peek(context), "texture:"))
		return (parse_texture_surface(context_pop(context, 8), shading));
	else
		return (throw_error(context, \
				"surface( 'color:' | 'cb' | 'texture:' )", P_T_STR));
}
