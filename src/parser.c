/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:47 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/27 03:35:23 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "get_next_line.h"
#include "parser.h"
#include "scene.h"
#include "utils.h"

int	parse_window_size(t_context *context)
{
	if (parse_int(ignore_space(context), get_range(RANGE_CLOSED, 400, 2000), &context->scene->window_width))
		return (throw_error(context, "window_size->width", P_T_WINDOW));
	if (parse_int(ignore_space(context), get_range(RANGE_CLOSED, 400, 2000), &context->scene->window_height))
		return (throw_error(context, "window_size->height", P_T_WINDOW));
	return (parse_endl(context));
}

int	parse_light(t_context *context)
{
	if (parse_double(ignore_space(context), get_named_range(RNG_POS), &context->scene->kld))
		return (throw_error(context, "light->kld", P_T_POS));
	if (parse_double(ignore_space(context), get_named_range(RNG_POS), &context->scene->kldd))
		return (throw_error(context, "light->kldd", P_T_POS));
	return (parse_endl(context));
}

static int	parse_line(t_context *context)
{
	ignore_space(context);
	if (streq_part(context_peek(context), "W"))
		return (parse_window_size(context_pop(context, 1)));
	else if (streq_part(context_peek(context), "A"))
		return (parse_ambient(context_pop(context, 1)));
	else if (streq_part(context_peek(context), "L"))
		return (parse_light(context_pop(context, 1)));
	else if (streq_part(context_peek(context), "C"))
		return (parse_camera(context_pop(context, 1)));
	else if (streq_part(context_peek(context), "li"))
		return (parse_spot_light(context_pop(context, 2)));
	else if (streq_part(context_peek(context), "sp"))
		return (parse_sphere(context_pop(context, 2)));
	else if (streq_part(context_peek(context), "cy"))
		return (parse_cylinder(context_pop(context, 2)));
	else if (streq_part(context_peek(context), "pl"))
		return (parse_plane(context_pop(context, 2)));
	else if (streq_part(context_peek(context), "#"))
		return (P_SUCCESS);
	else if (streq(context_peek(context), "\n"))
		return (P_SUCCESS);
	return (throw_error(context, "object idenfier", P_T_STR));
}

static int	open_scene(char *scene_name)
{
	int	fd;

	fd = open(scene_name, O_RDONLY);
	if (fd < 0)
	{
		ft_perror("miniRT");
		return (P_ERR_SYSCALL);
	}
	return (fd);
}

static int	parse_next_line(char *scene_name, int scene_fd, t_context *context)
{
	int	result;

	context->col = 0;
	context->line = get_next_line(scene_fd);
	if (!context->line)
		return (P_SUCCESS);
	result = parse_line(context);
	free(context->line);
	if (result == P_ERR_SYNTEX)
		print_parse_error(scene_name, context);
	context->row++;
	if (result == P_SUCCESS)
		result = P_CONTINUE;
	return (result);
}

int	parse_scene(char *scene_name, t_scene *scene, t_window *window)
{
	t_context	context;
	int			status;
	int			scene_fd;

	scene_fd = open_scene(scene_name);
	if (scene_fd < 0)
		return (P_ERR_SYSCALL);
	ft_memset(&context, 0, sizeof(t_context));
	ft_memset(scene, 0, sizeof(t_scene));
	context.window = window;
	context.scene = scene;
	errno = 0;
	status = P_CONTINUE;
	while (status == P_CONTINUE)
		status = parse_next_line(scene_name, scene_fd, &context);
	if (errno)
	{
		ft_perror("miniRT");
		return (P_ERR_SYSCALL);
	}
	return (status);
}
