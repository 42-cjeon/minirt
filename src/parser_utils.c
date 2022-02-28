/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 14:47:08 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

char	*context_peek(t_context *context)
{
	return (context->line + context->col);
}

t_context	*context_pop(t_context *context, int k)
{
	context->col += k;
	return (context);
}

t_context	*ignore_space(t_context *context)
{
	while (*context_peek(context) == ' ' || *context_peek(context) == '\t')
		context->col++;
	return (context);
}

int	throw_error(t_context *context, char *err_name, int err_type)
{
	context->err_name = err_name;
	context->err_type = err_type;
	return (P_ERR_SYNTEX);
}

int	print_parse_error(char *filename, t_context *context)
{
	char		buf[256];
	const char	*err_types[] = {
		"color3[0,255]",
		"point3(-INF,INF)",
		"vector3[-1,1]",
		"double(-INF,INF)",
		"double[0,1]",
		"double(0,180)",
		"string",
		"double[0,INF]"
	};

	ft_strlcpy(buf, filename, 256);
	ft_strlcat(buf, ":", 256);
	ft_strlcat(buf, ft_itoa(context->row + 1), 256);
	ft_strlcat(buf, ":", 256);
	ft_strlcat(buf, ft_itoa(context->col + 1), 256);
	ft_strlcat(buf, ": expected ", 256);
	ft_strlcat(buf, context->err_name, 256);
	ft_strlcat(buf, " <TYPE:", 256);
	ft_strlcat(buf, err_types[context->err_type], 256);
	ft_strlcat(buf, ">", 256);
	ft_puterror(buf);
	return (P_ERR_SYNTEX);
}
