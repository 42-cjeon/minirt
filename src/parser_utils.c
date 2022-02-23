/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:35:04 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 00:56:17 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ignore_space(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}

int	parse_endl(char *line)
{
	if (line == NULL)
		return (1);
	line = ignore_space(line);
	if (*line != '\n' && *line != '\0')
		return (1);
	return (0);
}

char	*parse_vector3(char *line, t_range range, t_vector3 *v)
{
	line = parse_double(line, range, &v->x);
	if (!line || *line != ',')
		return (NULL);
	line = parse_double(line + 1, range, &v->y);
	if (!line || *line != ',')
		return (NULL);
	return (parse_double(line + 1, range, &v->z));
}

char	*parse_point(char *line, double *d, int is_neg, t_range range)
{
	double	f;

	if (!ft_isdigit(*line))
		return (NULL);
	f = 10;
	while (ft_isdigit(*line))
	{
		if (is_neg)
			*d -= (double)(*line - '0') / f;
		else
			*d += (double)(*line - '0') / f;
		f *= 10;
		if (!is_in_range(*d, range))
			return (NULL);
		line++;
	}
	return (line);
}

char	*parse_double(char *line, t_range range, double *d)
{
	int	is_neg;

	is_neg = 0;
	*d = 0;
	if (*line == '-')
		is_neg = 1;
	if (*line == '-' || *line == '+')
		line += 1;
	if (!ft_isdigit(*line))
		return (NULL);
	while (ft_isdigit(*line))
	{
		*d *= 10;
		if (is_neg)
			*d -= (double)(*line - '0');
		else
			*d += (double)(*line - '0');
		if (!is_in_range(*d, range))
			return (NULL);
		line++;
	}
	if (*line == '.')
		return (parse_point(line + 1, d, is_neg, range));
	return (line);
}
