/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:47 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 00:33:39 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "get_next_line.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

static int	parse_line(char *line, t_scene *scene)
{
	line = ignore_space(line);
	if (streq_part(line, "A"))
		return (parse_ambient(line + 1, scene));
	else if (streq_part(line, "L"))
		return (parse_point_light(line + 1, scene));
	else if (streq_part(line, "C"))
		return (parse_camera(line + 1, scene));
	else if (streq_part(line, "sp"))
		return (parse_sphere(line + 2, scene));
	else if (streq_part(line, "cy"))
		return (parse_cylinder(line + 2, scene));
	else if (streq_part(line, "pl"))
		return (parse_plane(line + 2, scene));
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
