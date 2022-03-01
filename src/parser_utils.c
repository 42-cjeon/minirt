/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:52:10 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/01 13:27:33 by cjeon            ###   ########.fr       */
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

int	handle_sign(t_context *context)
{
	int	is_neg;

	if (*context_peek(context) == '-')
		is_neg = 1;
	else
		is_neg = 0;
	if (is_neg || *context_peek(context) == '+')
		context_pop(context, 1);
	return (is_neg);
}
