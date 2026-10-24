/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 16:46:13 by admoufle          #+#    #+#             */
/*   Updated: 2026/10/24 16:46:49 by admoufle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_gnl.h"

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
