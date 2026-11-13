/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 17:38:20 by me                #+#    #+#             */
/*   Updated: 2026/11/13 14:30:59 by me               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_struct.h"
#include "str.h"

#include <stdlib.h>
#include <stdbool.h>

void	free_light(t_light *lst)
{
	void	*ptr;

	while (lst)
	{
		ptr = lst;
		lst = lst->next;
		free(ptr);
	}
}

bool	add_light(t_light **head, t_light data)
{
	t_light	*node;

	node = malloc(sizeof(t_light));
	if (!node)
		return (false);
	ft_memcpy(node, &data, sizeof(t_light));
	node->next = *head;
	*head = node;
	return (true);
}
