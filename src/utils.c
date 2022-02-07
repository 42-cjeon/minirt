/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:48:19 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 14:42:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "utils.h"
#include "libft.h"

void	ft_puterror_prefix(void)
{
	ft_putendl_fd("Error", 2);
}

void	ft_perror(const char *executable)
{
	ft_puterror_prefix();
	perror(executable);
}

void	ft_puterror(const char *error_msg)
{
	ft_puterror_prefix();
	ft_putendl_fd(error_msg, 2);
}

int	streq(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int	streq_part(const char *heystack, const char *needle)
{
	while (*needle && *heystack)
	{
		if (*heystack != *needle)
			break ;
		heystack++;
		needle++;
	}
	if (*heystack == *needle || *needle == '\0')
		return (1);
	return (0);
}