/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:07:29 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 16:45:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector3.h"
# include "scene.h"

int		parse_scene(int scene_fd, t_scene *scene);
int		parse_line(char *line, t_scene *scene);
char	*ignore_space(char *line);
int		parse_cone(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_spot_light(char *line, t_scene *scene);
int		parse_point_light(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
char	*parse_double(char *line, double *d, t_range range);
char	*parse_point(char *line, double *d, int is_neg, t_range range);
char	*parse_vector3(char *line, t_range range, t_vector3 *v);

#endif