/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:48:19 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/09 16:52:38 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "scene.h"
#include "objects.h"
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

void print_vector3(t_vector3 v)
{
	printf("[x:%.3lf y:%.3lf z:%.3lf ]\n", v.x, v.y, v.z);
}

void print_color3(t_color3 c)
{
	printf("[R:%.2lf G:%.2lf B:%.2lf]\n", c.x, c.y, c.z);
}

void print_sphere(t_sphere *sp)
{
	printf("OBJ-SPHERE\n");
	printf("  -origin : "); print_vector3(sp->origin);
	printf("  -radius : %lf\n", sp->radius);
	printf("  -albedo : "); print_vector3(sp->phong.albedo);
}

void print_point_light(t_point_light *pl)
{
	printf("LIG-POINT\n");
	printf("  -origin : "); print_vector3(pl->origin);
	printf("  -ratio  : %lf\n", pl->ratio);
	printf("  -color  : "); print_color3(pl->color);
}

void print_objects(t_list *node)
{
	while (node)
	{
		if (node->type == OBJ_SPHERE)
			print_sphere(node->content);
		node = node->next;
	}
}

void print_lights(t_list *node)
{
	while (node)
	{
		if (node->type == LIG_POINT)
			print_point_light(node->content);
		node = node->next;
	}
}

void print_scene(t_scene *scene)
{
	printf("Ambient\n");
	printf("  -ratio : [%lf]\n", scene->gl.ratio);
	printf("  -color : "); print_color3(scene->gl.ambient);
	printf("Camera\n");
	printf("  -origin : "); print_vector3(scene->camera.ray.origin);
	printf("  -dir    : "); print_vector3(scene->camera.ray.dir);
	printf("  -fov    : [%lfrad]\n", scene->camera.fov_w);
	print_objects(scene->obj_list);
	print_lights(scene->light_list);
}