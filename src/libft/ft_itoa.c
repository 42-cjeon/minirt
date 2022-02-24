/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:43:04 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 15:23:52 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_to_str(char *buf, int n, int is_neg)
{
	int	start;

	start = 10;
	if (is_neg)
	{
		buf[start--] = '0' - (n % 10);
		n = -(n / 10);
	}
	else
	{
		buf[start--] = n % 10 + '0';
		n /= 10;
	}
	while (n)
	{
		buf[start--] = n % 10 + '0';
		n /= 10;
	}
	if (is_neg)
		buf[start--] = '-';
	return (start + 1);
}

char	*ft_itoa(int n)
{
	static char	buf[12];
	int			is_neg;
	int			start;

	buf[11] = '\0';
	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	start = convert_to_str(buf, n, is_neg);
	return (buf + start);
}
