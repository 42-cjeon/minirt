/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:19:39 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/16 13:04:04 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_buffers(t_buffer_head **hash_table, t_buffer_head *head, int fd)
{
	t_buffer		*curr;
	t_buffer		*next;
	t_buffer_head	*prev;

	curr = (head)->buffer;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	if (hash_table[fd % TABLE_SIZE] == head)
		hash_table[fd % TABLE_SIZE] = head->next;
	else
	{
		prev = hash_table[fd % TABLE_SIZE];
		while (prev->next != head)
			prev = prev->next;
		prev->next = head->next;
	}
	free(head);
	return (NULL);
}

t_buffer	*get_buffer(void)
{
	t_buffer	*new_buffer;

	new_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (new_buffer == NULL)
		return (NULL);
	new_buffer->end = 0;
	new_buffer->next = NULL;
	return (new_buffer);
}

t_buffer_head	*get_buffer_head(int fd)
{
	t_buffer_head	*head;

	head = (t_buffer_head *)malloc(sizeof(t_buffer_head));
	if (head == NULL)
		return (NULL);
	head->buffer = get_buffer();
	if (head->buffer == NULL)
	{
		free(head);
		return (NULL);
	}
	head->next = NULL;
	head->cursor = 0;
	head->fd = fd;
	return (head);
}

ssize_t	load_buffer(int fd, t_buffer *buffer)
{
	ssize_t	len;

	len = read(fd, buffer->data, BUFFER_SIZE);
	if (0 < len)
		buffer->end = len;
	return (len);
}

size_t	move_next_buffer(t_buffer_head *head, t_buffer **buffer)
{
	t_buffer	*next;

	next = (*buffer)->next;
	free(*buffer);
	head->buffer = next;
	*buffer = next;
	return (0);
}
