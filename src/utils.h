/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:52:01 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 14:42:29 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	ft_puterror(const char *error_msg);
void	ft_perror(const char *executable);
void	ft_puterror_prefix(void);
int		streq(const char *s1, const char *s2);
int		streq_part(const char *heystack, const char *needle);

#endif