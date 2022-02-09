/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:58:53 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/08 10:55:27 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

enum e_minirt_status
{
	RT_SUCCESS,
	RT_ERR_ARG,
	RT_ERR_FILE,
	RT_ERR_MLX,
	RT_ERR_SYSCALL
};

#endif