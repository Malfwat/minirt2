/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:46:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/10/25 14:36:41 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gnl.h"
#include "str.h"

void	free_gnl(t_buf **head)
{
	t_buf	*lst;
	void	*tmp;

	if (!*head)
		return ;
	lst = *head;
	*head = NULL;
	while (lst)
	{
		tmp = lst;
		free(lst->ptr);
		lst = lst->next;
		free(tmp);
	}
}

t_buf	*get_last_node(t_buf *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	concate(char *buffer, t_buf *head)
{
	size_t	len;

	while (head)
	{
		len = ft_strlen(head->ptr);
		ft_memcpy(buffer, head->ptr, len);
		head = head->next;
		buffer += len;
	}
	*buffer = 0;
}
