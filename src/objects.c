/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:23:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 22:47:00 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	hit_object(const t_ray *ray, t_list *list, t_hit_record *record)
{
	int	is_hit;

	record->distence = CAMERA_FAR;
	is_hit = 0;
	while (list)
	{
		if (list->type == OBJ_SPHERE)
			is_hit |= hit_sphere(ray, (t_sphere *)list->content, record);
		if (list->type == OBJ_CYLINDER)
			is_hit |= hit_cylinder(ray, (t_cylinder *)list->content, record);
		if (list->type == OBJ_PLANE)
			is_hit |= hit_plane(ray, (t_plane *)list->content, record);
		list = list->next;
	}
	return (is_hit);
}
