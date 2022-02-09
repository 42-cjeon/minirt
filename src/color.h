/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:52:09 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 15:37:17 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>
# include "vector3.h"

t_color3	v3_lerp(t_color3 from, t_color3 to, double p);
uint32_t	v3_to_color(t_color3 v);
void		trunc_color(t_vector3 *color);

void	trunc_color(t_vector3 *color);
uint32_t	v3_to_color(t_color3 v);
t_color3	v3_lerp(t_color3 from, t_color3 to, double p);

#endif