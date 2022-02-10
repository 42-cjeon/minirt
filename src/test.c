/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:58:24 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/10 16:12:11 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vector3.h"

int main(void)
{
	const t_vector3 a = {10, 0, 1};
	const t_vector3 b = {1, 0, 0};
	const t_vector3 c = v3_cross(b, a);

	printf("<%.3lf, %.3lf, %.3lf>\n", c.x, c.y, c.z);
	return (0);
}