/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: me <me@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:36:50 by me                #+#    #+#             */
/*   Updated: 2026/11/22 23:13:43 by me               ###   ########.fr       */
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

bool	is_line_empty(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (false);
		str++;
	}
	return (true);
}

void	null_terminate_component(char *str)
{
	char	*ptr;

	ptr = ft_strchr_set(str, RT_WSPACE);
	if (!ptr)
		ptr = ft_strchr(str, 0);
	*ptr = 0;
}
