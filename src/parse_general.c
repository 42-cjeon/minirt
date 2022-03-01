/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:35:04 by cjeon             #+#    #+#             */
/*   Updated: 2022/03/01 13:31:15 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_endl(t_context *context)
{
	ignore_space(context);
	if (*context_peek(context) != '\n' \
		&& *context_peek(context) != '\0')
		return (throw_error(context, "end of line", P_T_STR));
	return (P_SUCCESS);
}

int	parse_vector3(t_context *context, t_range range, t_vector3 *v)
{
	if (parse_double(context, range, &v->x) \
		|| *context_peek(context) != ',')
		return (P_ERR_SYNTEX);
	context_pop(context, 1);
	if (parse_double(context, range, &v->y) \
		|| *context_peek(context) != ',')
		return (P_ERR_SYNTEX);
	context_pop(context, 1);
	return (parse_double(context, range, &v->z));
}

int	parse_point(t_context *context, double *d, int is_neg, t_range range)
{
	int	f;
	int	digits;

	digits = 0;
	if (!ft_isdigit(*context_peek(context)))
		return (P_ERR_SYNTEX);
	f = 10;
	while (ft_isdigit(*context_peek(context)) && digits <= MAX_DIGITS)
	{
		if (is_neg)
			*d -= (double)(*context_peek(context) - '0') / f;
		else
			*d += (double)(*context_peek(context) - '0') / f;
		f *= 10;
		context_pop(context, 1);
		digits++;
	}
	if (!is_in_range(*d, range) || MAX_DIGITS < digits)
		return (P_ERR_SYNTEX);
	return (P_SUCCESS);
}

int	parse_double(t_context *context, t_range range, double *d)
{
	int	is_neg;
	int	digits;

	digits = 0;
	is_neg = handle_sign(context);
	*d = 0;
	if (!ft_isdigit(*context_peek(context)))
		return (P_ERR_SYNTEX);
	while (ft_isdigit(*context_peek(context)) && digits <= MAX_DIGITS)
	{
		*d *= 10;
		if (is_neg)
			*d -= (double)(*context_peek(context) - '0');
		else
			*d += (double)(*context_peek(context) - '0');
		context_pop(context, 1);
		digits++;
	}
	if (!is_in_range(*d, range) || MAX_DIGITS < digits)
		return (P_ERR_SYNTEX);
	if (*context_peek(context) == '.')
		return (parse_point(context_pop(context, 1), d, is_neg, range));
	return (P_SUCCESS);
}

int	parse_int(t_context *context, t_range range, int *k)
{
	int	is_neg;
	int	digits;

	digits = 0;
	is_neg = handle_sign(context);
	*k = 0;
	if (!ft_isdigit(*context_peek(context)))
		return (P_ERR_SYNTEX);
	while (ft_isdigit(*context_peek(context)) && digits <= MAX_DIGITS)
	{
		*k *= 10;
		if (is_neg)
			*k -= (*context_peek(context) - '0');
		else
			*k += (*context_peek(context) - '0');
		context_pop(context, 1);
		digits++;
	}
	if (!is_in_range(*k, range) || MAX_DIGITS < digits)
		return (P_ERR_SYNTEX);
	return (P_SUCCESS);
}
