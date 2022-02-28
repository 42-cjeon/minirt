/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:22:25 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 20:54:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"

int	throw_error(t_context *context, char *err_name, int err_type)
{
	context->err_name = err_name;
	context->err_type = err_type;
	return (P_ERR_SYNTEX);
}

int	print_parse_error(char *filename, t_context *context)
{
	char		buf[512];
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

	ft_strlcpy(buf, filename, 512);
	ft_strlcat(buf, ":", 512);
	ft_strlcat(buf, ft_itoa(context->row + 1), 512);
	ft_strlcat(buf, ":", 512);
	ft_strlcat(buf, ft_itoa(context->col + 1), 512);
	ft_strlcat(buf, ": expected ", 512);
	ft_strlcat(buf, context->err_name, 512);
	ft_strlcat(buf, " <TYPE:", 512);
	ft_strlcat(buf, err_types[context->err_type], 512);
	ft_strlcat(buf, ">", 512);
	ft_puterror(buf);
	return (P_ERR_SYNTEX);
}

void	print_component_error(char *scene_name, char *component)
{
	char	buf[512];

	ft_strlcpy(buf, scene_name, 512);
	ft_strlcat(buf, ": ", 512);
	ft_strlcat(buf, component, 512);
	ft_strlcat(buf, ": missing necessary component", 512);
	ft_puterror(buf);
}

void	print_dup_error(char *filename, t_context *context)
{
	char	buf[512];

	ft_strlcpy(buf, filename, 512);
	ft_strlcat(buf, ":", 512);
	ft_strlcat(buf, ft_itoa(context->row + 1), 512);
	ft_strlcat(buf, ":", 512);
	ft_strlcat(buf, ft_itoa(context->col), 512);
	ft_strlcat(buf, ": ", 512);
	ft_strlcat(buf, context->err_name, 512);
	ft_strlcat(buf, ": duplicated component found", 512);
	ft_puterror(buf);
}

int	throw_dup_error(t_context *context, char *component)
{
	context->err_name = component;
	return (P_ERR_DUP);
}
