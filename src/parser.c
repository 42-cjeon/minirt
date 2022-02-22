/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:47 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/21 13:59:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "get_next_line.h"
#include "libft.h"
#include "utils.h"
#include "parser.h"
#include "ft_window.h"
#include "objects.h"

const static t_range	g_01_range = {1, 0.0, 1.0};
const static t_range	g_u8_range = {1, 0.0, 255.0};
const static t_range	g_unit_v3_range = {1, -1.0, 1.0};
const static t_range	g_fov_range = {0, 0.0, 180.0};
const static t_range	g_inf_range = {1, -INFINITY, INFINITY};

int	parse_endl(char *line)
{
	if (line == NULL)
		return (1);
	line = ignore_space(line);
	if (*line != '\n' && *line != '\0')
		return (1);
	return (0);
}

char *parse_vector3(char *line, t_range range, t_vector3 *v)
{
	line = parse_double(line, &v->x, range);
	if (!line || *line != ',')
		return (NULL);
	line = parse_double(line + 1, &v->y, range);
	if (!line || *line != ',')
		return (NULL);
	return (parse_double(line + 1, &v->z, range));
}

char *parse_point(char *line, double *d, int is_neg, t_range range)
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

char *parse_double(char *line, double *d, t_range range)
{
	int		is_neg;

	is_neg = 0;
	*d = 0;
	if (*line == '-' || *line == '+')
	{
		if (*line == '-')
			is_neg = 1;
		line += 1;
	}
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

int parse_ambient(char *line, t_scene *scene)
{
	line = ignore_space(line);
	line = parse_double(line, &scene->gl.ratio, g_01_range);
	if (!line)
		return (1);
	line = ignore_space(line);
	line = parse_vector3(line, g_u8_range, &scene->gl.ambient);
	if (!line)
		return (1);
	scene->gl.ambient = v3_rescale(scene->gl.ambient, g_u8_range, g_01_range);
	return (parse_endl(line));
}

int parse_point_light_fail(t_point_light *pl)
{
	free(pl);
	return (1);
}

int parse_point_light(char *line, t_scene *scene)
{
	t_point_light *pl;
	t_list *node;

	pl = malloc(sizeof(t_point_light));
	if (pl == NULL)
		return (2);
	line = parse_vector3(ignore_space(line), g_inf_range, &pl->origin);
	if (line == NULL)
		return (parse_point_light_fail(pl));
	line = parse_double(ignore_space(line), &pl->ratio, g_01_range);
	if (line == NULL)
		return (parse_point_light_fail(pl));
	line = parse_vector3(ignore_space(line), g_u8_range, &pl->color);
	if (line == NULL)
		return (parse_point_light_fail(pl));
	node = ft_lstnew(LIG_POINT, pl);
	if (node == NULL)
	{
		free(pl);
		return (2);
	}
	pl->color = v3_rescale(pl->color, g_u8_range, g_01_range);
	ft_lstadd_front(&scene->light_list, node);
	return (parse_endl(line));
}

int parse_spot_light(char *line, t_scene *scene)
{
	return (999);
}

int parse_camera(char *line, t_scene *scene)
{
	line = ignore_space(line);
	line = parse_vector3(line, g_inf_range, &scene->camera.ray.origin);
	if (line == NULL)
		return (1);
	line = ignore_space(line);
	line = parse_vector3(line, g_unit_v3_range, &scene->camera.ray.dir);
	if (line == NULL)
		return (1);
	line = ignore_space(line);
	line = parse_double(line, &scene->camera.fov_w, g_fov_range);
	if (line == NULL)
		return (1);
	scene->camera.fov_w = scene->camera.fov_w / 180 * M_PI;
	scene->camera.fov_h = scene->camera.fov_w / ASPECT_RATIO;
	return (parse_endl(line));
}

int parse_sphere_fail(t_sphere *sp)
{
	free(sp);
	return (1);
}

int parse_sphere(char *line, t_scene *scene)
{
	t_sphere	*sp;
	t_list		*node;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		return (2);
	line = parse_vector3(ignore_space(line), g_inf_range, &sp->origin);
	if (line == NULL)
		return (parse_sphere_fail(sp));
	line = parse_double(ignore_space(line), &sp->radius, g_inf_range);
	if (line == NULL)
		return (parse_sphere_fail(sp));
	line = parse_vector3(ignore_space(line), g_u8_range, &sp->phong.albedo);
	if (line == NULL)
		return (parse_sphere_fail(sp));
	node = ft_lstnew(OBJ_SPHERE, sp);
	if (node == NULL)
	{
		free(sp);
		return (2);
	}
	ft_lstadd_front(&scene->obj_list, node);
	sp->phong.albedo = v3_rescale(sp->phong.albedo, g_u8_range, g_01_range);
	return (parse_endl(line));
}

int parse_cylinder_fail(t_cylinder *cy)
{
	free(cy);
	return (1);
}

int parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	*cy;
	t_list		*node;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		return (2);
	line = parse_vector3(ignore_space(line), g_inf_range, &cy->origin);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	line = parse_vector3(ignore_space(line), g_01_range, &cy->dir);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	line = parse_double(ignore_space(line), &cy->diameter, g_inf_range);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	line = parse_double(ignore_space(line), &cy->height, g_inf_range);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	line = parse_vector3(ignore_space(line), g_u8_range, &cy->phong.albedo);
	if (line == NULL)
		return (parse_cylinder_fail(cy));
	node = ft_lstnew(OBJ_CYLINDER, cy);
	if (node == NULL)
	{
		free(cy);
		return (2);
	}
	cy->phong.albedo = v3_rescale(cy->phong.albedo, g_u8_range, g_01_range);
	ft_lstadd_front(&scene->obj_list, node);
	return (parse_endl(line));
}

static int parse_plane_fail(t_plane *pl)
{
	free(pl);
	return (1);
}

int parse_plane(char *line, t_scene *scene)
{
	t_plane	*pl;
	t_list	*node;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		return (2);
	line = parse_vector3(ignore_space(line), g_inf_range, &pl->origin);
	if (line == NULL)
		return (parse_plane_fail(pl));
	line = parse_vector3(ignore_space(line), g_inf_range, &pl->normal);
	if (line == NULL)
		return (parse_plane_fail(pl));
	line = parse_vector3(ignore_space(line), g_u8_range, &pl->phong.albedo);
	if (line == NULL)
		return (parse_plane_fail(pl));
	node = ft_lstnew(OBJ_PLANE, pl);
	if (node == NULL)
	{
		free(pl);
		return (2);
	}
	ft_lstadd_front(&scene->obj_list, node);
	pl->phong.albedo = v3_rescale(pl->phong.albedo, g_u8_range, g_01_range);
	return (parse_endl(line));
}

int parse_cone(char *line, t_scene *scene)
{
	return (999);
}

char *ignore_space(char *line)
{
	while(ft_isspace(*line))
		line++;
	return (line);
}

int parse_line(char *line, t_scene *scene)
{
	line = ignore_space(line);
	if (streq_part(line, "A"))
		return (parse_ambient(line + 1, scene));
	else if (streq_part(line, "L"))
		return (parse_point_light(line + 1, scene));
	else if (streq_part(line, "C"))
		return (parse_camera(line + 1, scene));
	else if (streq_part(line, "li"))
		return (parse_spot_light(line + 2, scene));
	else if (streq_part(line, "sp"))
		return (parse_sphere(line + 2, scene));
	else if (streq_part(line, "cy"))
		return (parse_cylinder(line + 2, scene));
	else if (streq_part(line, "pl"))
		return (parse_plane(line + 2, scene));
	else if (streq_part(line, "co"))
		return (parse_cone(line + 2, scene));
	else if (streq(line, "\n"))
		return (0);
	return (1);
}

int	parse_scene(int scene_fd, t_scene *scene)
{
	char	*line;

	ft_memset(scene, 0, sizeof(t_scene));
	errno = 0;
	while (42)
	{
		line = get_next_line(scene_fd);
		if (!line)
			break ;
		if (parse_line(line, scene))
		{
			free(line);
			ft_puterror("miniRT: parse: syntex error");
			return (1);
		}
		free(line);
	}
	if (errno)
	{
		ft_perror("miniRT: parse");
		return (1);
	}
	return (0);
}
