/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/28 20:43:53 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector3.h"
# include "scene.h"

enum	e_parser_status
{
	P_SUCCESS,
	P_CONTINUE,
	P_ERR_SYNTEX,
	P_ERR_MISSING,
	P_ERR_DUP,
	P_ERR_SYSCALL
};

enum	e_err_type
{
	P_T_COLOR,
	P_T_POINT,
	P_T_UNITV,
	P_T_DOUBLE,
	P_T_RATIO,
	P_T_FOV,
	P_T_STR,
	P_T_POS
};

typedef struct s_context
{
	char		*line;
	int			row;
	int			col;
	int			err_type;
	char		*err_name;
	t_window	*window;
	t_scene		*scene;
}	t_context;

int			add_texture(t_context *context, int type, char *name);
char		*context_peek(t_context *context);
t_context	*context_pop(t_context *context, int k);
t_context	*ignore_space(t_context *context);
int			parse_ambient(t_context *context);
int			parse_camera(t_context *context);
int			parse_cylinder(t_context *context);
int			parse_double(t_context *context, t_range range, double *d);
int			parse_endl(t_context *context);
int			parse_int(t_context *context, t_range range, int *k);
int			parse_light(t_context *context);
int			parse_plane(t_context *context);
int			parse_point(t_context *context, double *d, \
						int is_neg, t_range range);
int			parse_scene(char *scene_name, t_scene *scene, t_window *window);
int			parse_shading(t_context *context, t_shading *shading);
int			parse_sphere(t_context *context);
int			parse_spot_light(t_context *context);
int			parse_surface(t_context *context, t_shading *shading);
int			parse_texture(t_context *context, int type, char **pstr);
int			parse_vector3(t_context *context, t_range range, t_vector3 *v);
int			print_parse_error(char *filename, t_context *context);
int			throw_error(t_context *context, char *err_name, int err_type);
int			throw_dup_error(t_context *context, char *component);
void		print_component_error(char *scene_name, char *component);
void		print_dup_error(char *filename, t_context *context);
#endif