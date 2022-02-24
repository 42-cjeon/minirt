/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/24 18:43:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector3.h"
# include "scene.h"

enum	e_parser_status
{
	P_SUCCESS,
	P_ERR_SYNTEX,
	P_ERR_SYSCALL,
	P_END
};

enum	e_err_type
{
	P_T_COLOR,
	P_T_POINT,
	P_T_UNITV,
	P_T_DOUBLE,
	P_T_RATIO,
	P_T_FOV,
	P_T_STR
};

typedef struct s_context
{
	char	*line;
	int		row;
	int		col;
	int		fail;
	int		err_type;
	char	*err_name;

}	t_context;

t_context	*ignore_space(t_context *context);
t_context	*context_pop(t_context *context, int k);
char		*context_peek(t_context *context);
int			parse_double(t_context *context, t_range range, double *d);
int			parse_endl(t_context *context);
int			parse_vector3(t_context *context, t_range range, t_vector3 *v);
int			parse_ambient(t_context *context, t_scene *scene);
int			parse_camera(t_context *context, t_scene *scene);
int			parse_cylinder(t_context *context, t_scene *scene);
int			parse_plane(t_context *context, t_scene *scene);
int			parse_point_light(t_context *context, t_scene *scene);
int			parse_sphere(t_context *context, t_scene *scene);
int			parse_scene(char *scene_name, t_scene *scene);
int			print_parse_error(char *filename, t_context *context);
int			throw_error(t_context *context, char *err_name, int err_type);
#endif