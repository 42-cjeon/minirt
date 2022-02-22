/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:52:01 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 01:12:09 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "scene.h"
#include "vector3.h"

void	ft_puterror(const char *error_msg);
void	ft_perror(const char *executable);
void	ft_puterror_prefix(void);
int		streq(const char *s1, const char *s2);
int		streq_part(const char *heystack, const char *needle);

void print_scene(t_scene *scene);
void print_vector3(t_vector3 v);

#endif