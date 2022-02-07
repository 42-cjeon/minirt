/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:44:04 by cjeon             #+#    #+#             */
/*   Updated: 2022/02/07 13:01:26 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_with_func(t_list *lst, t_list_apply f, \
										t_list_del del)
{
	void	*new_content;
	t_list	*node;

	new_content = f(lst->type, lst->content);
	if (new_content == NULL)
		return (NULL);
	node = ft_lstnew(lst->type, new_content);
	if (node == NULL)
	{
		if (del != NULL)
			del(lst->type, new_content);
		return (NULL);
	}
	return (node);
}

static t_list	*ft_lstappend(t_list **head, t_list *tail, t_list *new)
{
	if (*head == NULL)
		*head = new;
	else
		tail->next = new;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, t_list_apply f, t_list_del del)
{
	t_list	*new_lst_head;
	t_list	*new_lst_tail;
	t_list	*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst_head = NULL;
	new_lst_tail = NULL;
	while (lst)
	{
		node = ft_lstnew_with_func(lst, f, del);
		if (node == NULL)
		{
			ft_lstclear(&new_lst_head, del);
			return (NULL);
		}
		new_lst_tail = ft_lstappend(&new_lst_head, new_lst_tail, node);
		lst = lst->next;
	}
	return (new_lst_head);
}
