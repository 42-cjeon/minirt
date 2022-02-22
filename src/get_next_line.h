/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:19:31 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/23 01:12:58 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define GNL_BUFFER_SIZE 1024
# define GNL_TABLE_SIZE 1

#include <stdlib.h>
#include <unistd.h>

typedef struct s_buffer
{
	size_t			end;
	unsigned char	data[GNL_BUFFER_SIZE];
	struct s_buffer	*next;
}	t_buffer;

typedef struct s_buffer_head
{
	int						fd;
	size_t					cursor;
	t_buffer				*buffer;
	struct s_buffer_head	*next;
}	t_buffer_head;

char			*get_next_line(int fd);
t_buffer_head	*search_buffer_head(t_buffer_head **hash_table, int fd);
size_t			get_total_len(t_buffer_head **hash_table, t_buffer_head *head,
					size_t start, int fd);
ssize_t			alloc_and_read_buffer(t_buffer *buffer, int fd);
void			*free_buffers(t_buffer_head **hash_table,
					t_buffer_head *head, int fd);
t_buffer		*get_buffer(void);
ssize_t			load_buffer(int fd, t_buffer *buffer);
size_t			move_next_buffer(t_buffer_head *head, t_buffer **buffer);
char			*copy_buffer(t_buffer_head **hash_table, t_buffer_head *head,
					size_t total_len, int fd);
t_buffer_head	*get_buffer_head(int fd);

#endif